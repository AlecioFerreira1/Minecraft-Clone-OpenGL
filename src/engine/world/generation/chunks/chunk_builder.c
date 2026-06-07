#include "chunk_builder.h"
#include "../../registry/block_registry.h"
#include "../../world.h"

ChunkBuilder chunk_builder_create(HashMap* chunks, TextureAtlas* textures) {
  ChunkBuilder chunkBuilder;

  chunkBuilder.chunks = chunks;
  chunkBuilder.textures = textures;

  return chunkBuilder;
}

static void chunk_builder_build_chunk_mesh(ChunkBuilder* chunkBuilder, Chunk* chunk) {
  float* vertices = NULL;
  size_t floatCount = 0;
  Vec3 chunkPosOnWorld = chunk_coords_to_world_coords(chunk->coords);
  const float cubeSize = 1.f;

  for(uint8_t x = 0; x < CHUNK_SIZE; ++x) {
    for(uint8_t y = 0; y < CHUNK_SIZE; ++y) {
      for(uint8_t z = 0; z < CHUNK_SIZE; ++z) {
        if(chunk->blocks[x][y][z] == BLOCK_AIR) continue;

        Vec3 blockPosOnWorld = vec3_sum(
          chunkPosOnWorld, 
          (Vec3){
            .x = (float)x, 
            .y = (float)y, 
            .z = (float)z
          }
        );

        Block topNeighbour = world_block_at(
          chunkBuilder->chunks, (Vec3) {.x = blockPosOnWorld.x, .y = blockPosOnWorld.y + cubeSize, .z = blockPosOnWorld.z}
        );
        
        Block bottomNeighbour = world_block_at(
          chunkBuilder->chunks, (Vec3) {.x = blockPosOnWorld.x, .y = blockPosOnWorld.y - cubeSize, .z = blockPosOnWorld.z}
        );
        
        Block leftNeighbour = world_block_at(
          chunkBuilder->chunks, (Vec3) {.x = blockPosOnWorld.x - cubeSize, .y = blockPosOnWorld.y, .z = blockPosOnWorld.z}
        );
        
        Block rightNeighbour = world_block_at(
          chunkBuilder->chunks, (Vec3) {.x = blockPosOnWorld.x + cubeSize, .y = blockPosOnWorld.y, .z = blockPosOnWorld.z}
        );
        
        Block frontNeighbour = world_block_at(
          chunkBuilder->chunks, (Vec3) {.x = blockPosOnWorld.x, .y = blockPosOnWorld.y, .z = blockPosOnWorld.z + cubeSize}
        );
        
        Block backNeighbour = world_block_at(
          chunkBuilder->chunks, (Vec3) {.x = blockPosOnWorld.x, .y = blockPosOnWorld.y, .z = blockPosOnWorld.z - cubeSize}
        );

        UVrect topFaceUv = uv_rect_convert(REGISTERED_BLOCKS[chunk->blocks[x][y][z]].top, chunkBuilder->textures);
        UVrect bottomFaceUv = uv_rect_convert(REGISTERED_BLOCKS[chunk->blocks[x][y][z]].bottom, chunkBuilder->textures);
        UVrect leftFaceUv = uv_rect_convert(REGISTERED_BLOCKS[chunk->blocks[x][y][z]].left, chunkBuilder->textures);
        UVrect rightFaceUv = uv_rect_convert(REGISTERED_BLOCKS[chunk->blocks[x][y][z]].right, chunkBuilder->textures);
        UVrect frontFaceUv = uv_rect_convert(REGISTERED_BLOCKS[chunk->blocks[x][y][z]].front, chunkBuilder->textures);
        UVrect backFaceUv = uv_rect_convert(REGISTERED_BLOCKS[chunk->blocks[x][y][z]].back, chunkBuilder->textures);

        if(topNeighbour == BLOCK_AIR) {
          add_face_vertices_to_chunk(
            &vertices, &floatCount, 
            quad_gen_vertices(blockPosOnWorld, cubeSize, cubeSize, (Vec3) {0, 1, 0}, topFaceUv)
          );
        }

        if(bottomNeighbour == BLOCK_AIR) {
          add_face_vertices_to_chunk(
            &vertices, &floatCount, 
            quad_gen_vertices(blockPosOnWorld, cubeSize, cubeSize, (Vec3) {0, -1, 0}, bottomFaceUv)
          ); 
        }

        if(leftNeighbour == BLOCK_AIR) {
          add_face_vertices_to_chunk(
            &vertices, &floatCount, 
            quad_gen_vertices(blockPosOnWorld, cubeSize, cubeSize, (Vec3) {-1, 0, 0}, leftFaceUv)
          );
        }

        if(rightNeighbour == BLOCK_AIR) {
          add_face_vertices_to_chunk(
            &vertices, &floatCount, 
            quad_gen_vertices(blockPosOnWorld, cubeSize, cubeSize, (Vec3) {1, 0, 0}, rightFaceUv)
          );
        }

        if(frontNeighbour == BLOCK_AIR) {
          add_face_vertices_to_chunk(
            &vertices, &floatCount, 
            quad_gen_vertices(blockPosOnWorld, cubeSize, cubeSize, (Vec3) {0, 0, 1}, frontFaceUv)
          );
        }

        if(backNeighbour == BLOCK_AIR) {
          add_face_vertices_to_chunk(
            &vertices, &floatCount, 
            quad_gen_vertices(blockPosOnWorld, cubeSize, cubeSize, (Vec3) {0, 0, -1}, backFaceUv)
          );
        }
      }
    }
  }

  chunk->mesh = mesh_create(vertices, floatCount / 5, 5 * sizeof(float), GL_STATIC_DRAW);
  free(vertices);
}

static void add_face_vertices_to_chunk(float** chunkVertices, size_t* nValues, float* quad) {
  float* moreSpaceToNewQuad = realloc(*chunkVertices, ((*nValues) + 30) * sizeof(float));

  if(moreSpaceToNewQuad != NULL) {
    *chunkVertices = moreSpaceToNewQuad;
    memcpy(*chunkVertices + (*nValues), quad, 30 * sizeof(float));
    *nValues = (*nValues) + 30;
  }

  free(quad);
}

void chunk_builder_update_chunks(ChunkBuilder* chunkBuilder) {
  for(size_t i = 0; i < chunkBuilder->chunks->capacity; ++i) {
    if(chunkBuilder->chunks->entries[i].key != NULL) {
      Chunk* chunk = (Chunk*) chunkBuilder->chunks->entries[i].value;

      if(chunk->dirty) {
        chunk_builder_build_chunk_mesh(chunkBuilder, chunk);
        chunk->dirty = false;
      }
    }
  }
}
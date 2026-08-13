#include "chunk_builder.h"
#include "../world.h"
#include "greedy_meshing.h"

static const float BLOCK_SIZE = 1.f;

ChunkBuilder chunk_builder_create(HashMap *chunks, TextureAtlas *textures) {
  ChunkBuilder chunkBuilder;

  chunkBuilder.chunks = chunks;
  chunkBuilder.textures = textures;
  chunkBuilder.rebuildBudget = 4;
  chunkBuilder.rebuildQueue = priority_queue_create(sizeof(ChunkJob), chunk_job_compare);

  return chunkBuilder;
}

static void chunk_builder_build_chunk_mesh(ChunkBuilder *chunkBuilder, Chunk *chunk) {
  Vector vertices = vector_create(VECTOR_MIN_CAPACITY * CHUNK_SIZE, sizeof(Vertex));
  
  Vector chunk_neg_x = build_2D_chunk_slice(chunkBuilder, chunk, (Vec3) {-1, 0, 0});
  Vector chunk_pos_x = build_2D_chunk_slice(chunkBuilder, chunk, (Vec3) {1, 0, 0});
  Vector chunk_neg_y = build_2D_chunk_slice(chunkBuilder, chunk, (Vec3) {0, -1, 0});
  Vector chunk_pos_y = build_2D_chunk_slice(chunkBuilder, chunk, (Vec3) {0, 1, 0});
  Vector chunk_neg_z = build_2D_chunk_slice(chunkBuilder, chunk, (Vec3) {0, 0, -1});
  Vector chunk_pos_z = build_2D_chunk_slice(chunkBuilder, chunk, (Vec3) {0, 0, 1});

  add_chunk_slice_to_vertices(&vertices, &chunk_neg_x);
  add_chunk_slice_to_vertices(&vertices, &chunk_pos_x);
  add_chunk_slice_to_vertices(&vertices, &chunk_neg_y);
  add_chunk_slice_to_vertices(&vertices, &chunk_pos_y);
  add_chunk_slice_to_vertices(&vertices, &chunk_neg_z);
  add_chunk_slice_to_vertices(&vertices, &chunk_pos_z);

  mesh_destroy(chunk->mesh);

  chunk->mesh = mesh_create((Vertex *) vertices.data, vertices.size, GL_STATIC_DRAW);

  vector_destroy(&vertices);
}

static void add_chunk_slice_to_vertices(Vector *vertices, Vector *chunkSliceVertices) {
  vector_append_many(vertices, chunkSliceVertices);
  vector_destroy(chunkSliceVertices);
}

void chunk_builder_update_chunks(ChunkBuilder *chunkBuilder, Vec3 playerPos) {
  ChunkCoords playerChunk = world_coords_to_chunk_coords(playerPos);

  for(size_t i = 0; i < chunkBuilder->chunks->capacity; ++i) {
    if(chunkBuilder->chunks->entries[i].key != NULL) {
      Chunk *chunk = (Chunk *) chunkBuilder->chunks->entries[i].value;

      if(chunk->dirty && chunk->state == CHUNK_STATE_ACTIVE) {
        int distanceToplayer = 
          (playerChunk.x - chunk->coords.x) * (playerChunk.x - chunk->coords.x) +
          (playerChunk.y - chunk->coords.y) * (playerChunk.y - chunk->coords.y) +
          (playerChunk.z - chunk->coords.z) * (playerChunk.z - chunk->coords.z)
        ;

        ChunkJob chunkJob = {distanceToplayer, chunk->coords};  

        priority_queue_push(&chunkBuilder->rebuildQueue, &chunkJob);
        chunk->dirty = false;
      }
    }
  }
  
  int8_t budget = chunkBuilder->rebuildBudget;

  while(budget > 0 && !priority_queue_is_empty(&chunkBuilder->rebuildQueue)) {
    ChunkJob *chunkJob = (ChunkJob *) priority_queue_peek(&chunkBuilder->rebuildQueue);
    Chunk *chunk = world_get_chunk(chunkBuilder->chunks, chunkJob->coords);
  
    if(chunk != NULL) {
      chunk_builder_build_chunk_mesh(chunkBuilder, chunk);
    }

    priority_queue_pop(&chunkBuilder->rebuildQueue);
    budget--;
  }
}

static Vector build_2D_chunk_slice(ChunkBuilder *chunkBuilder, const Chunk *chunk, Vec3 normal) {
  Vector vertices = vector_create(VECTOR_MIN_CAPACITY * CHUNK_SIZE, sizeof(Vertex));
  const Vec3 chunkPosOnWorld = chunk_coords_to_world_coords(chunk->coords);
  uint16_t mask[CHUNK_SIZE][CHUNK_SIZE];

  memset(mask, BLOCK_AIR, sizeof(mask));

  if(normal.x == 1 || normal.x == -1) {
    for(uint8_t x = 0; x < CHUNK_SIZE; ++x) { 
      for(uint8_t y = 0 ; y < CHUNK_SIZE; ++y) { 
        for(uint8_t z = 0 ; z < CHUNK_SIZE; ++z) { 
          if(chunk->blocks[x][y][z] == BLOCK_AIR) continue;

          Vec3 neighbourBlockOnWorldPos = vec3_sum(
            chunkPosOnWorld, (Vec3) {
              .x = (float)x + (BLOCK_SIZE * normal.x), 
              .y = (float)y + (BLOCK_SIZE * normal.y), 
              .z = (float)z + (BLOCK_SIZE * normal.z)
            }
          ); 
            
          if(world_block_at(chunkBuilder->chunks, neighbourBlockOnWorldPos) == BLOCK_AIR) 
            mask[y][z] = chunk->blocks[x][y][z];
        }   
      } 

      greedy_meshing(&vertices, &mask, chunkPosOnWorld, (float)x, normal, BLOCK_SIZE, chunkBuilder->textures);
    }
  } 

  else if(normal.y == 1 || normal.y == -1) {
    for(uint8_t y = 0; y < CHUNK_SIZE; ++y) { 
      for(uint8_t x = 0 ; x < CHUNK_SIZE; ++x) { 
        for(uint8_t z = 0 ; z < CHUNK_SIZE; ++z) { 
          if(chunk->blocks[x][y][z] == BLOCK_AIR) continue;

          Vec3 neighbourBlockOnWorldPos = vec3_sum(
            chunkPosOnWorld, (Vec3) {
              .x = (float)x + (BLOCK_SIZE * normal.x),  
              .y = (float)y + (BLOCK_SIZE * normal.y), 
              .z = (float)z + (BLOCK_SIZE * normal.z)
            }
          ); 
            
          if(world_block_at(chunkBuilder->chunks, neighbourBlockOnWorldPos) == BLOCK_AIR) 
            mask[x][z] = chunk->blocks[x][y][z]; 
        }   
      } 

      greedy_meshing(&vertices, &mask, chunkPosOnWorld, (float)y, normal, BLOCK_SIZE, chunkBuilder->textures);
    }
  }

  else {
    for(uint8_t z = 0; z < CHUNK_SIZE; ++z) { 
      for(uint8_t x = 0 ; x < CHUNK_SIZE; ++x) { 
        for(uint8_t y = 0 ; y < CHUNK_SIZE; ++y) { 
          if(chunk->blocks[x][y][z] == BLOCK_AIR) continue;

          Vec3 neighbourBlockOnWorldPos = vec3_sum(
            chunkPosOnWorld, (Vec3) {
              .x = (float)x + (BLOCK_SIZE * normal.x), 
              .y = (float)y + (BLOCK_SIZE * normal.y), 
              .z = (float)z + (BLOCK_SIZE * normal.z)
            }
          ); 
            
          if(world_block_at(chunkBuilder->chunks, neighbourBlockOnWorldPos) == BLOCK_AIR) 
            mask[x][y] = chunk->blocks[x][y][z];
        }   
      }
      
      greedy_meshing(&vertices, &mask, chunkPosOnWorld, (float)z, normal, BLOCK_SIZE, chunkBuilder->textures);
    }
  }

  return vertices;
}
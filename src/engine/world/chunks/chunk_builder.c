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
  chunkBuilder.hasPlayerChunk = false;

  return chunkBuilder;
}

static void chunk_builder_build_chunk_mesh(ChunkBuilder *chunkBuilder, Chunk *chunk) {
  VerticesGroup verticesGroup = vertices_group_create();
  const Vec3 chunkPosOnWorld = chunk_coords_to_world_coords(chunk->coords);

  uint16_t mask_neg_x[CHUNK_SIZE][CHUNK_SIZE] = {BLOCK_AIR};
  uint16_t mask_pos_x[CHUNK_SIZE][CHUNK_SIZE]= {BLOCK_AIR};
  uint16_t mask_neg_y[CHUNK_SIZE][CHUNK_SIZE]= {BLOCK_AIR};
  uint16_t mask_pos_y[CHUNK_SIZE][CHUNK_SIZE]= {BLOCK_AIR};
  uint16_t mask_neg_z[CHUNK_SIZE][CHUNK_SIZE]= {BLOCK_AIR};
  uint16_t mask_pos_z[CHUNK_SIZE][CHUNK_SIZE]= {BLOCK_AIR};

  for(uint8_t i = 0; i < CHUNK_SIZE; ++i) { 
    for(uint8_t j = 0 ; j < CHUNK_SIZE; ++j) { 
      for(uint8_t k = 0 ; k < CHUNK_SIZE; ++k) { 
        if(chunk->blocks[i][j][k] != BLOCK_AIR) {
          fill_mask_by_axis_in_coords_ijk(chunkBuilder->chunks, chunk, &mask_neg_x, (Vec3) {-1, 0, 0}, i, j, k);
          fill_mask_by_axis_in_coords_ijk(chunkBuilder->chunks, chunk, &mask_pos_x, (Vec3) {1, 0, 0}, i, j, k); 
        }

        if(chunk->blocks[j][i][k] != BLOCK_AIR) {
          fill_mask_by_axis_in_coords_ijk(chunkBuilder->chunks, chunk, &mask_neg_y, (Vec3) {0, -1, 0}, i, j, k);
          fill_mask_by_axis_in_coords_ijk(chunkBuilder->chunks, chunk, &mask_pos_y, (Vec3) {0, 1, 0}, i, j, k); 
        }

        if(chunk->blocks[j][k][i] != BLOCK_AIR) {
          fill_mask_by_axis_in_coords_ijk(chunkBuilder->chunks, chunk, &mask_neg_z, (Vec3) {0, 0, -1}, i, j, k);
          fill_mask_by_axis_in_coords_ijk(chunkBuilder->chunks, chunk, &mask_pos_z, (Vec3) {0, 0, 1}, i, j, k); 
        }
      }   
    } 
      
    greedy_meshing(&verticesGroup, &mask_neg_x, chunkPosOnWorld, (float)i, (Vec3) {-1, 0, 0}, chunkBuilder->textures);
    greedy_meshing(&verticesGroup, &mask_pos_x, chunkPosOnWorld, (float)i + BLOCK_SIZE, (Vec3) {1, 0, 0}, chunkBuilder->textures);
    greedy_meshing(&verticesGroup, &mask_neg_y, chunkPosOnWorld, (float)i, (Vec3) {0, -1, 0}, chunkBuilder->textures);
    greedy_meshing(&verticesGroup, &mask_pos_y, chunkPosOnWorld, (float)i + BLOCK_SIZE, (Vec3) {0, 1, 0}, chunkBuilder->textures);
    greedy_meshing(&verticesGroup, &mask_neg_z, chunkPosOnWorld, (float)i, (Vec3) {0, 0, -1}, chunkBuilder->textures);
    greedy_meshing(&verticesGroup, &mask_pos_z, chunkPosOnWorld, (float)i + BLOCK_SIZE, (Vec3) {0, 0, 1}, chunkBuilder->textures);
  }

  Vector vertices = vector_create(VECTOR_MIN_CAPACITY, sizeof(Vertex));
  Vector subMeshes = vector_create(3, sizeof(SubMesh));

  SubMesh opaqueSubmesh = {0, vector_size(&verticesGroup.opaqueVertices), RENDER_MODE_OPAQUE};
  SubMesh cutoutSubmesh = {vector_size(&verticesGroup.opaqueVertices), vector_size(&verticesGroup.cutoutVertices), RENDER_MODE_CUTOUT};
  SubMesh blendSubmesh = {
    vector_size(&verticesGroup.opaqueVertices) + vector_size(&verticesGroup.cutoutVertices), 
    vector_size(&verticesGroup.blendVertices), RENDER_MODE_BLEND
  };

  vector_append_many(&vertices, &verticesGroup.opaqueVertices);
  vector_append_many(&vertices, &verticesGroup.cutoutVertices);
  vector_append_many(&vertices, &verticesGroup.blendVertices);

  vector_push_back(&subMeshes, &opaqueSubmesh);
  vector_push_back(&subMeshes, &cutoutSubmesh);
  vector_push_back(&subMeshes, &blendSubmesh);

  mesh_destroy(chunk->mesh);

  chunk->mesh = mesh_create((Vertex *) vertices.data, vertices.size, &subMeshes, GL_STATIC_DRAW);

  vector_destroy(&vertices);
  vector_destroy(&subMeshes);
  vertices_group_destroy(&verticesGroup);
}

static void fill_mask_by_axis_in_coords_ijk(
  HashMap *chunks, const Chunk *chunk, uint16_t (*mask)[CHUNK_SIZE][CHUNK_SIZE], 
  Vec3 normal, uint8_t i, uint8_t j, uint8_t k
) {
  const Vec3 chunkPosOnWorld = chunk_coords_to_world_coords(chunk->coords);
  uint16_t neighbourBlockType;
  Vec3 neighbourBlockOnWorldPos;
  
  if(normal.x == -1) {
    neighbourBlockOnWorldPos = vec3_sum(chunkPosOnWorld, (Vec3) {(float)i - BLOCK_SIZE, (float)j, (float) k});
    neighbourBlockType = i > 0 ? chunk->blocks[i - 1][j][k] : world_block_at(chunks, neighbourBlockOnWorldPos);
    
    if(neighbourBlockType == BLOCK_AIR || (neighbourBlockType == BLOCK_WATER && chunk->blocks[i][j][k] != BLOCK_WATER)) 
      (*mask)[j][k] = chunk->blocks[i][j][k];
  }

  else if(normal.x == 1) {
    neighbourBlockOnWorldPos = vec3_sum(chunkPosOnWorld, (Vec3) {(float)i + BLOCK_SIZE, (float)j, (float) k});
    neighbourBlockType = i < (CHUNK_SIZE - 1) ? chunk->blocks[i + 1][j][k] : world_block_at(chunks, neighbourBlockOnWorldPos);
    
    if(neighbourBlockType == BLOCK_AIR || (neighbourBlockType == BLOCK_WATER && chunk->blocks[i][j][k] != BLOCK_WATER)) 
      (*mask)[j][k] = chunk->blocks[i][j][k];
  }

  else if(normal.y == -1) {
    neighbourBlockOnWorldPos = vec3_sum(chunkPosOnWorld, (Vec3) {(float)j, (float)i - BLOCK_SIZE, (float)k});
    neighbourBlockType = i > 0 ? chunk->blocks[j][i - 1][k] : world_block_at(chunks, neighbourBlockOnWorldPos);
    
    if(neighbourBlockType == BLOCK_AIR || (neighbourBlockType == BLOCK_WATER && chunk->blocks[j][i][k] != BLOCK_WATER)) 
      (*mask)[k][j] = chunk->blocks[j][i][k];
  }

  else if(normal.y == 1) {
    neighbourBlockOnWorldPos = vec3_sum(chunkPosOnWorld, (Vec3) {(float)j, (float)i + BLOCK_SIZE, (float)k});
    neighbourBlockType = i < (CHUNK_SIZE - 1) ? chunk->blocks[j][i + 1][k] : world_block_at(chunks, neighbourBlockOnWorldPos);
    
    if(neighbourBlockType == BLOCK_AIR || (neighbourBlockType == BLOCK_WATER && chunk->blocks[j][i][k] != BLOCK_WATER)) 
      (*mask)[k][j] = chunk->blocks[j][i][k];
  }

  else if(normal.z == -1) {
    neighbourBlockOnWorldPos = vec3_sum(chunkPosOnWorld, (Vec3) {(float)j, (float)k, (float)i - BLOCK_SIZE});
    neighbourBlockType = i > 0 ? chunk->blocks[j][k][i - 1] : world_block_at(chunks, neighbourBlockOnWorldPos);
    
    if(neighbourBlockType == BLOCK_AIR || (neighbourBlockType == BLOCK_WATER && chunk->blocks[j][k][i] != BLOCK_WATER)) 
      (*mask)[k][j] = chunk->blocks[j][k][i];
  }

  else {
    neighbourBlockOnWorldPos = vec3_sum(chunkPosOnWorld, (Vec3) {(float)j, (float)k, (float)i + BLOCK_SIZE});
    neighbourBlockType = i < (CHUNK_SIZE - 1) ? chunk->blocks[j][k][i + 1] : world_block_at(chunks, neighbourBlockOnWorldPos);
    
    if(neighbourBlockType == BLOCK_AIR || (neighbourBlockType == BLOCK_WATER && chunk->blocks[j][k][i] != BLOCK_WATER)) 
      (*mask)[k][j] = chunk->blocks[j][k][i];
  }
}

void chunk_builder_update_chunks(ChunkBuilder *chunkBuilder, Vec3 playerPos) {
  ChunkCoords playerChunk = world_coords_to_chunk_coords(playerPos);

  if(!chunkBuilder->hasPlayerChunk || !chunk_coords_equals(playerChunk, chunkBuilder->lastPlayerChunk)) {
    WorldConfig worldConfig = world_config_get();
    int renderDistanceEndChunk = worldConfig.renderDistance;
    int renderDistanceStartChunk = renderDistanceEndChunk * -1;
    char chunkName[128];

    while(!priority_queue_is_empty(&chunkBuilder->rebuildQueue)) {
      ChunkJob *chunkJob = priority_queue_peek(&chunkBuilder->rebuildQueue);
      Chunk *chunk = world_get_chunk(chunkBuilder->chunks, chunkJob->coords);

      if(chunk != NULL) chunk->queued = false;
      priority_queue_pop(&chunkBuilder->rebuildQueue);
    }

    for(int x = renderDistanceEndChunk; x >= renderDistanceStartChunk; --x){
      for(int y = worldConfig.worldMinHeight; y < worldConfig.worldMaxHeight; y += CHUNK_SIZE){
        for(int z = renderDistanceEndChunk; z >= renderDistanceStartChunk; --z){
          ChunkCoords chunkCoords = {x + playerChunk.x, y / CHUNK_SIZE, z + playerChunk.z};

          snprintf(
            chunkName, sizeof(chunkName), "chunk_%d_%d_%d", 
            chunkCoords.x, chunkCoords.y, chunkCoords.z
          );

          Chunk *chunk = world_get_chunk(chunkBuilder->chunks, chunkCoords);

          if(chunk != NULL && chunk->dirty && chunk->state == CHUNK_STATE_ACTIVE && !chunk->queued) {
            int distanceToplayer = 
              (playerChunk.x - chunk->coords.x) * (playerChunk.x - chunk->coords.x) +
              (playerChunk.y - chunk->coords.y) * (playerChunk.y - chunk->coords.y) +
              (playerChunk.z - chunk->coords.z) * (playerChunk.z - chunk->coords.z)
            ;

            ChunkJob chunkJob = {distanceToplayer, chunk->coords};  

            priority_queue_push(&chunkBuilder->rebuildQueue, &chunkJob);
            chunk->queued = true;
          }
        }
      }
    } 

    chunkBuilder->hasPlayerChunk = true;
    chunkBuilder->lastPlayerChunk = playerChunk;
  } 
  
  int8_t budget = chunkBuilder->rebuildBudget;

  while(budget > 0 && !priority_queue_is_empty(&chunkBuilder->rebuildQueue)) {
    ChunkJob *chunkJob = (ChunkJob *) priority_queue_peek(&chunkBuilder->rebuildQueue);
    Chunk *chunk = world_get_chunk(chunkBuilder->chunks, chunkJob->coords);
  
    if(chunk != NULL) {
      chunk_builder_build_chunk_mesh(chunkBuilder, chunk);

      chunk->dirty = false;
      chunk->queued = false;
      budget--;
    }

    priority_queue_pop(&chunkBuilder->rebuildQueue);
  }
}
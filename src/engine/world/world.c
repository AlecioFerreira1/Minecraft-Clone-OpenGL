#include "world.h"

World world_create(WorldType worldType) {
  World world;

  world.config = world_config_get();
  world.worldGenerator = world_generator_create(world.config.seed, worldType);
  world.type = worldType;
  world.destroyBudget = 4;
  world.destroyQueue = priority_queue_create(sizeof(ChunkJob), chunk_job_compare);
  world.hasPlayerChunk = false;
  
  hash_map_create(&world.chunks, 11);

  return world;
}

void world_destroy(World *world) {
  hash_map_destroy(&world->chunks);
  priority_queue_destroy(&world->destroyQueue);
  world_generator_remove_resources(&world->worldGenerator);
}

void world_update(World *world, Vec3 playerPos) {
  ChunkCoords playerChunk = world_coords_to_chunk_coords(playerPos);
  int renderDistanceEndChunk = world->config.renderDistance;
  int renderDistanceStartChunk = renderDistanceEndChunk * -1;

  if(!world->hasPlayerChunk || !chunk_coords_equals(world->lastPlayerChunk, playerChunk)) {
    char chunkName[128];

    for(int x = renderDistanceEndChunk; x >= renderDistanceStartChunk; --x){
      for(int y = world->config.worldMinHeight; y < world->config.worldMaxHeight; y += CHUNK_SIZE){
        for(int z = renderDistanceEndChunk; z >= renderDistanceStartChunk; --z){
          ChunkCoords chunkCoords = {x + playerChunk.x, y / CHUNK_SIZE, z + playerChunk.z};

          snprintf(chunkName, sizeof(chunkName), "chunk_%d_%d_%d", chunkCoords.x, chunkCoords.y, chunkCoords.z);

          Chunk *chunk = hash_map_get_value(&world->chunks, chunkName);

          if(chunk == NULL) {
            chunk = chunk_create(chunkCoords, &world->worldGenerator);
            
            hash_map_insert(&world->chunks, chunkName, chunk);
            world_mark_dirty(world, chunkCoords); 
          } 

          else chunk->state = CHUNK_STATE_ACTIVE;
        }
      }
    } 
  }

  world_discard_chunks_out_of_range(world, playerChunk, renderDistanceStartChunk, renderDistanceEndChunk); 

  world->lastPlayerChunk = playerChunk;
  world->hasPlayerChunk = true;
}

static void world_discard_chunks_out_of_range(World *world, ChunkCoords playerChunk, int renderDistanceStart, int renderDistanceEnd) {
  if(!world->hasPlayerChunk || !chunk_coords_equals(world->lastPlayerChunk, playerChunk)) { 
    for(size_t i = 0; i < world->chunks.capacity; ++i) {
      if(world->chunks.entries[i].key != NULL) {
        Chunk *chunk = (Chunk *) world->chunks.entries[i].value;

        if(chunk->state != CHUNK_STATE_ACTIVE) continue;

        if((chunk->coords.x) < (renderDistanceStart + playerChunk.x) || 
          (chunk->coords.z) < (renderDistanceStart + playerChunk.z) ||
          (chunk->coords.x) > (renderDistanceEnd + playerChunk.x) ||
          (chunk->coords.z) > (renderDistanceEnd + playerChunk.z)
        ) {
          int distanceToplayer = 
            (playerChunk.x - chunk->coords.x) * (playerChunk.x - chunk->coords.x) +
            (playerChunk.y - chunk->coords.y) * (playerChunk.y - chunk->coords.y) +
            (playerChunk.z - chunk->coords.z) * (playerChunk.z - chunk->coords.z)
          ;

          chunk->state = CHUNK_STATE_PENDING_UNLOAD;

          ChunkJob chunkJob = {distanceToplayer, chunk->coords};

          priority_queue_push(&world->destroyQueue, &chunkJob);
        }
      }
    }
  }

  int8_t budget = world->destroyBudget;
  char chunkName[128];

  while(budget > 0 && !priority_queue_is_empty(&world->destroyQueue)) {
    ChunkJob *chunkJob = (ChunkJob *) priority_queue_peek(&world->destroyQueue);
    Chunk *chunk = world_get_chunk(&world->chunks, chunkJob->coords);

    if(chunk != NULL && chunk->state == CHUNK_STATE_PENDING_UNLOAD) {
      snprintf(
        chunkName, sizeof(chunkName),
        "chunk_%d_%d_%d", 
        chunk->coords.x, chunk->coords.y, chunk->coords.z
      );

      hash_map_delete_key(&world->chunks, chunkName);
      chunk_destroy(chunk);
      budget--;
    }

    priority_queue_pop(&world->destroyQueue);
  }
}

uint16_t world_block_at(HashMap *chunks, Vec3 worldCoords) {
  const ChunkCoords chunkCoords = world_coords_to_chunk_coords(worldCoords);
  Chunk *chunk = world_get_chunk(chunks, chunkCoords);

  if(chunk == NULL) return BLOCK_AIR;

  return chunk->blocks
    [(uint8_t) (worldCoords.x - (float) (chunkCoords.x * CHUNK_SIZE))]
    [(uint8_t) (worldCoords.y - (float) (chunkCoords.y * CHUNK_SIZE))]
    [(uint8_t) (worldCoords.z - (float) (chunkCoords.z * CHUNK_SIZE))]
  ;
}

static void world_mark_dirty(World *world, ChunkCoords chunkCoords) {
  ChunkCoords neighBoursChunkCoords[6] = {
    {chunkCoords.x, chunkCoords.y + 1, chunkCoords.z},
    {chunkCoords.x, chunkCoords.y - 1, chunkCoords.z},
    {chunkCoords.x - 1, chunkCoords.y, chunkCoords.z},
    {chunkCoords.x + 1, chunkCoords.y, chunkCoords.z},
    {chunkCoords.x, chunkCoords.y, chunkCoords.z + 1},
    {chunkCoords.x, chunkCoords.y, chunkCoords.z - 1},
  };

  for(uint8_t i = 0; i < 6; ++i) {
    Chunk *chunk = world_get_chunk(&world->chunks, neighBoursChunkCoords[i]);

    if(chunk != NULL) chunk->dirty = true;
  }
}

Chunk *world_get_chunk(HashMap *chunks, ChunkCoords chunkCoords) {
  char chunkName[128];

  snprintf(chunkName, sizeof(chunkName), "chunk_%d_%d_%d", chunkCoords.x, chunkCoords.y, chunkCoords.z);

  return (Chunk *) hash_map_get_value(chunks, chunkName);
}
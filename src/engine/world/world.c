#include "world.h"

World world_create(WorldType worldType) {
  World world;

  world.config = world_config_get();
  world.worldGenerator = world_generator_create(world.config.seed, worldType);
  world.type = worldType;
  
  hash_map_create(&world.chunks, 10);

  return world;
}

void world_destroy(World* world) {
  hash_map_destroy(&world->chunks);
}

void world_update(World* world, Vec3 playerPos) {
  float renderDistanceEndBlock = (float) (CHUNK_SIZE * (world->config.renderDistance + 1));
  float renderDistanceStartBlock = renderDistanceEndBlock * -1.f;
  char chunkName[128];

  WorldTypeConfig worldTypeConfig = world_type_get_config(world->type);

  for(float x = renderDistanceEndBlock; x >= renderDistanceStartBlock; x -= (float) CHUNK_SIZE){
    for(float y = (float) worldTypeConfig.minHeigth; y < (float) worldTypeConfig.maxHeigth; y += (float) CHUNK_SIZE){
      for(float z = renderDistanceEndBlock; z >= renderDistanceStartBlock; z -= (float)CHUNK_SIZE){
        Vec3 currentChunkPos = (Vec3){x + playerPos.x, y, z + playerPos.z};
        ChunkCoords chunkCoords = world_coords_to_chunk_coords(currentChunkPos);

        snprintf(
          chunkName, sizeof(chunkName), 
          "chunk_%d_%d_%d", 
          chunkCoords.x, chunkCoords.y, chunkCoords.z
        );

        if(!chunk_already_loaded(&world->chunks, chunkName)) {
          hash_map_insert(&world->chunks, chunkName, chunk_create(currentChunkPos, &world->worldGenerator));
          world_mark_dirty(world, chunkCoords); 
        } 
      }
    }
  } 

  // world_discard_chunks_out_of_range(world, playerPos, renderDistanceStartBlock, renderDistanceEndBlock); 
}

static void world_discard_chunks_out_of_range(World* world, Vec3 playerPos, float renderDistanceStart, float renderDistanceEnd) {
  for(size_t i = 0; i < world->chunks.capacity; ++i) {
    if(world->chunks.entries[i].key != NULL) {
      Chunk* chunk = (Chunk*) world->chunks.entries[i].value;

      if(((float) chunk->coords.x) < renderDistanceStart + playerPos.x || 
        ((float) chunk->coords.z) < renderDistanceStart + playerPos.z ||
        ((float) chunk->coords.x) > renderDistanceEnd + playerPos.x || 
        ((float) chunk->coords.z) > renderDistanceEnd + playerPos.z
      ) {
        char chunkName[128];

        snprintf(
          chunkName, sizeof(chunkName), 
          "chunk_%d_%d_%d", 
          chunk->coords.x, chunk->coords.y, chunk->coords.z
        );
  
        hash_map_delete_key(&world->chunks, chunkName);
        free(chunk);
      }
    }
  }
}

uint16_t world_block_at(HashMap* chunks, Vec3 worldCoords) {
  char chunkName[128];
  const ChunkCoords chunkCoords = world_coords_to_chunk_coords(worldCoords);

  snprintf(
    chunkName, sizeof(chunkName), 
    "chunk_%d_%d_%d", 
    chunkCoords.x, chunkCoords.y, chunkCoords.z
  );

  Chunk* chunk = (Chunk*) hash_map_get_value(chunks, chunkName);

  if(chunk == NULL) return BLOCK_AIR;

  return chunk->blocks
    [(uint8_t) (worldCoords.x - (float) (chunkCoords.x * CHUNK_SIZE))]
    [(uint8_t) (worldCoords.y - (float) (chunkCoords.y * CHUNK_SIZE))]
    [(uint8_t) (worldCoords.z - (float) (chunkCoords.z * CHUNK_SIZE))]
  ;
}

static bool chunk_already_loaded(HashMap* chunks, char* chunkName) {
  return hash_map_search(chunks, chunkName) != -1;
}

static void world_mark_dirty(World* world, ChunkCoords chunkCoords) {
  ChunkCoords neighBoursChunkCoords[6] = {
    {chunkCoords.x, chunkCoords.y + 1, chunkCoords.z},
    {chunkCoords.x, chunkCoords.y - 1, chunkCoords.z},
    {chunkCoords.x - 1, chunkCoords.y, chunkCoords.z},
    {chunkCoords.x + 1, chunkCoords.y, chunkCoords.z},
    {chunkCoords.x, chunkCoords.y, chunkCoords.z + 1},
    {chunkCoords.x, chunkCoords.y, chunkCoords.z - 1},
  };

  char chunkName[128];

  for(uint8_t i = 0; i < 6; ++i) {
    snprintf(
      chunkName, sizeof(chunkName), 
      "chunk_%d_%d_%d", 
      neighBoursChunkCoords[i].x, neighBoursChunkCoords[i].y, neighBoursChunkCoords[i].z
    );

    Chunk* chunk = (Chunk*) hash_map_get_value(&world->chunks, chunkName);

    if(chunk != NULL) chunk->dirty = true;
  }
}
#include "world_generator.h"
#include "../chunks/chunk.h"

WorldGenerator world_generator_create(int32_t seed, WorldType worldType) {
  WorldGenerator generator;

  generator.seed = seed;
  generator.worldType = worldType;
  generator.config.superflat = superflat_get_config();
  generator.config.default_ = default_get_config();

  return generator;
}

void world_generator_generate_chunk(WorldGenerator *generator, Chunk *chunk) {
  switch(generator->worldType) {
    case WORLD_TYPE_SUPERFLAT:
      generate_super_flat(generator, chunk);
      break;
    
    case WORLD_TYPE_DEFAULT:
      generate_default(generator, chunk);
      break;
    
    case WORLD_TYPE_CUSTOM:
      generate_super_flat(generator, chunk);
      break;

    default:
      generate_super_flat(generator, chunk);
      break;
  }
}

void world_generator_remove_resources(WorldGenerator *generator) {
  free(generator->config.superflat.layers);
}   

static void generate_super_flat(WorldGenerator *generator, Chunk *chunk) {
  const Vec3 chunkCoordsOnWorldCoords = chunk_coords_to_world_coords(chunk->coords);

  for(int y = 0; y < CHUNK_SIZE; ++y) {
    float currentHeight = chunkCoordsOnWorldCoords.y + y;

    for(int x = 0; x < CHUNK_SIZE; ++x) {
      for(int z = 0; z < CHUNK_SIZE; ++z) {
        chunk->blocks[x][y][z] = superflat_get_block_on_y_level(generator->config.superflat, currentHeight);
      }
    }
  }
}

static void generate_default(WorldGenerator *generator, Chunk *chunk) {
  const Vec3 chunkCoordsOnWorldCoords = chunk_coords_to_world_coords(chunk->coords);
  const float maxTerrainHeight = generator->config.default_.maxTerrainHeight;

  for(uint8_t x = 0; x < CHUNK_SIZE; ++x) {
    for(uint8_t z = 0; z < CHUNK_SIZE; ++z) {
      Vec3 worldCoords = vec3_sum(chunkCoordsOnWorldCoords, (Vec3) {(float)x, 0.f, (float)z});
      float height = default_terrain_height_generation(generator->config.default_, worldCoords, generator->seed);
      
      for(uint8_t y = 0; y < CHUNK_SIZE; ++y) {
        float currentHeight = chunkCoordsOnWorldCoords.y + y;

        if(currentHeight <= height && currentHeight <= maxTerrainHeight) {
          chunk->blocks[x][y][z] = default_get_block_on_y_level(generator->config.default_, currentHeight);
        }

        else if(currentHeight <= maxTerrainHeight && currentHeight <= generator->config.default_.waterMaxHeight) {
          chunk->blocks[x][y][z] = BLOCK_WATER;
        }

        else chunk->blocks[x][y][z] = BLOCK_AIR;
      }
    }
  }
}
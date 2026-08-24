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
  uint16_t block = BLOCK_AIR;

  for(int y = 0; y < CHUNK_SIZE; ++y) {
    int yTarget = (int) chunk_coords_to_world_coords(chunk->coords).y + y;
    const bool minHeightExceeded = yTarget < generator->config.superflat.minHeigth; 
    const bool maxHeightExceeded = yTarget > generator->config.superflat.maxHeigth;

    if(!minHeightExceeded && !maxHeightExceeded) {
      int layer = generator->config.superflat.minHeigth; 
      
      for(size_t i = 0; i < generator->config.superflat.nLayers; ++i){ 
        if(yTarget < layer) break; 
        
        block = generator->config.superflat.layers[i].block; 
        layer += generator->config.superflat.layers[i].quantity; 
      } 
      
      if(layer <= yTarget) block = BLOCK_AIR;
    }

    for(int x = 0; x < CHUNK_SIZE; ++x) {
      for(int z = 0; z < CHUNK_SIZE; ++z) {
        chunk->blocks[x][y][z] = block;
      }
    }
  }
}

static void generate_default(WorldGenerator *generator, Chunk *chunk) {
  const float baseHeight = generator->config.default_.baseTerrainHeight;
  const float amplitude = generator->config.default_.amplitude;
  const float frequency = generator->config.default_.frequency;
  const Vec3 chunkCoordsOnWorldCoords = chunk_coords_to_world_coords(chunk->coords);

  for(uint8_t x = 0; x < CHUNK_SIZE; ++x) {
    for(uint8_t z = 0; z < CHUNK_SIZE; ++z) {
      Vec3 worldCoords = vec3_sum(chunkCoordsOnWorldCoords, (Vec3) {(float) x, 0.f, (float) z});
      float noise = noise2D(worldCoords.x * frequency, worldCoords.z * frequency, generator->seed);
      float height = baseHeight + noise * amplitude;
      
      for(uint8_t y = 0; y < CHUNK_SIZE; ++y) {
        if((chunkCoordsOnWorldCoords.y + y) < height) {
          chunk->blocks[x][y][z] = default_get_block_by_y_level(generator->config.default_, chunkCoordsOnWorldCoords.y + y);
        }

        else {
          chunk->blocks[x][y][z] = BLOCK_AIR;
        }
      }
    }
  }
}
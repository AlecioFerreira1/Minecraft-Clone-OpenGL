#include "world_generator.h"
#include "../chunks/chunk.h"

WorldGenerator world_generator_create(uint32_t seed, WorldType worldType) {
  WorldGenerator generator;

  generator.seed = seed;
  generator.worldType = worldType;
  generator.worldTypeConfig = world_type_get_config(worldType);

  return generator;
}

void world_generator_generate_chunk(WorldGenerator *generator, Chunk *chunk) {
  switch(generator->worldType) {
    case WORLD_TYPE_SUPERFLAT:
      generate_super_flat(generator, chunk);
      break;
    
    case WORLD_TYPE_DEFAULT:
      break;
    
    case WORLD_TYPE_CUSTOM:
      break;

    default:
      generate_super_flat(generator, chunk);
      break;
  }
}

void world_generator_remove_resources(WorldGenerator *generator) {
  free(generator->worldTypeConfig.layers);
}   

static void generate_super_flat(WorldGenerator *generator, Chunk *chunk) {
  uint16_t block = BLOCK_AIR;

  for(int y = 0; y < CHUNK_SIZE; ++y) {
    int yTarget = (int) chunk_coords_to_world_coords(chunk->coords).y + y;
    const bool minHeightExceeded = yTarget < generator->worldTypeConfig.minHeigth; 
    const bool maxHeightExceeded = yTarget > generator->worldTypeConfig.maxHeigth;

    if(!minHeightExceeded && !maxHeightExceeded) {
      int layer = generator->worldTypeConfig.minHeigth; 
      
      for(size_t i = 0; i < generator->worldTypeConfig.nLayers; ++i){ 
        if(yTarget < layer) break; 
        
        block = generator->worldTypeConfig.layers[i].block; 
        layer += generator->worldTypeConfig.layers[i].quantity; 
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
#include "world_generator.h"
#include "../world.h"

WorldGenerator world_generator_create(uint32_t seed, WorldType worldType) {
  WorldGenerator generator;

  generator.seed = seed;
  generator.worldType = worldType;

  return generator;
}

uint16_t world_generator_generate_block(WorldGenerator *generator, ChunkCoords chunkCoords, uint8_t localChunkX, uint8_t localChunkY, uint8_t localChunkZ) {
  const WorldTypeConfig worldTypeConfig = world_type_get_config(generator->worldType);
  const uint32_t yTarget = ((uint32_t) floor(chunk_coords_to_world_coords(chunkCoords).y)) + localChunkY;
  
  const bool minHeightExceeded = yTarget < worldTypeConfig.minHeigth;
  const bool maxHeightExceeded = yTarget > worldTypeConfig.maxHeigth;

  uint16_t block = BLOCK_AIR;

  if(!minHeightExceeded && !maxHeightExceeded) {
    int layer = worldTypeConfig.minHeigth;

    for(size_t i = 0; i < worldTypeConfig.nLayers; ++i){
      if(yTarget < layer) break;

      block = worldTypeConfig.layers[i].block;
      layer += worldTypeConfig.layers[i].quantity;
    }

    if(layer <= yTarget) {
      block = BLOCK_AIR;
    }
  }
   
  free(worldTypeConfig.layers);
  return block;
}
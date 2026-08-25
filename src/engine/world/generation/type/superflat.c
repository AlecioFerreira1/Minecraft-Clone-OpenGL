#include "superflat.h"
#include "../../../config/world_config.h"

Superflat superflat_get_config() {
  Superflat config;

  config.minHeigth = world_config_get().worldMinHeight;
  config.maxHeigth = world_config_get().worldMaxHeight;

  BlockLayer layers[] = {  
    {.block = BLOCK_BEDROCK, .quantity = 1},
    {.block = BLOCK_STONE, .quantity = 60}, 
    {.block = BLOCK_DIRT, .quantity = 4}, 
    {.block = BLOCK_GRASS, .quantity = 1},
  };

  config.nLayers = sizeof(layers) / sizeof(layers[0]);
  config.layers = malloc(sizeof(BlockLayer) * config.nLayers);

  memcpy(config.layers, layers, sizeof(layers));

  return config;
}

Block superflat_get_block_on_y_level(Superflat config, float worldY) {
  if(worldY > 65.f || worldY < config.minHeigth) return BLOCK_AIR;
  if(worldY > 60.f) return BLOCK_GRASS;
  if(worldY > 0.f) return BLOCK_STONE;
  else return BLOCK_BEDROCK;
}
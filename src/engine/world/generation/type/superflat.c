#include "superflat.h"
#include "../../../config/world_config.h"

WorldTypeConfig superflat_get_config() {
  WorldTypeConfig config;

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
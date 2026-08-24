#include "default.h"

Default default_get_config() {
  Default config;

  config.maxHeigth = world_config_get().worldMaxHeight;
  config.maxHeigth = world_config_get().worldMinHeight;
  config.baseTerrainHeight = 66.f;
  config.maxTerrainHeight = 128.f;
  config.amplitude = (config.maxTerrainHeight - config.baseTerrainHeight) - 40.f;
  config.frequency = 0.01f;

  return config;
}

Block default_get_block_by_y_level(Default config, float worldY) {
  if(worldY > config.maxTerrainHeight || worldY < config.minHeigth) return BLOCK_AIR;
  if(worldY > config.baseTerrainHeight) return BLOCK_GRASS;
  if(worldY > 2.f) return BLOCK_STONE;
  else return BLOCK_BEDROCK;
}
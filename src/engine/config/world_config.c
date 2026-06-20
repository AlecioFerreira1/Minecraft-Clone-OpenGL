#include "world_config.h"

WorldConfig world_config_get() {
  WorldConfig config;

  config.renderDistance = 8;
  config.worldHeight = 256;
  config.seed = 174619303;

  return config;
}
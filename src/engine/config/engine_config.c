#include "engine_config.h"

EngineConfig engine_config_get() {
  EngineConfig config;

  config.windowWidth = 1600;
  config.windowHeight = 1000;
  config.vsync = true;
  config.blockSize = 1.f;

  return config;
}
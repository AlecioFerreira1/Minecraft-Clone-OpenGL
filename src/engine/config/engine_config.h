#pragma once

#include <stdbool.h>

typedef struct {
  int windowWidth;
  int windowHeight;
  bool vsync;
  float blockSize;
} EngineConfig;

EngineConfig engine_config_get();
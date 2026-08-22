#pragma once

#include <stdint.h>

#define CHUNK_SIZE 16

typedef struct {
  int worldMaxHeight;
  int worldMinHeight;
  uint8_t renderDistance;
  int seed;
} WorldConfig;

WorldConfig world_config_get();
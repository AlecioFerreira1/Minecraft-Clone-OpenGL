#pragma once

#include <stdint.h>

#define CHUNK_SIZE 16

typedef struct {
  int worldMaxHeight;
  int worldMinHight;
  uint8_t renderDistance;
  int seed;
} WorldConfig;

WorldConfig world_config_get();
#pragma once

#include <stdint.h>

#define CHUNK_SIZE 16

typedef struct {
  int worldHeight;
  uint8_t renderDistance;
  uint32_t seed;
} WorldConfig;

WorldConfig world_config_get();
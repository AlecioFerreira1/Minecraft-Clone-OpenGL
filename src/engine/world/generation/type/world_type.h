#pragma once

#include <stdint.h>

#include "../../block/block.h"

typedef enum {
  WORLD_TYPE_SUPERFLAT, 
  WORLD_TYPE_DEFAULT, 
  WORLD_TYPE_CUSTOM
} WorldType;

typedef struct {
  Block block;
  uint16_t quantity;
} BlockLayer;

typedef struct {
  BlockLayer* layers;
  size_t nLayers;
  int minHeigth;
  int maxHeigth;
} WorldTypeConfig;

WorldTypeConfig world_type_get_config(WorldType worldType);
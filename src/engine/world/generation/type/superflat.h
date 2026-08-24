#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "world_type.h"
#include "../../block/block.h"

typedef struct {
  Block block;
  uint16_t quantity;
} BlockLayer;

typedef struct {
  BlockLayer *layers;
  size_t nLayers;
  int minHeigth;
  int maxHeigth;
} Superflat;

Superflat superflat_get_config();
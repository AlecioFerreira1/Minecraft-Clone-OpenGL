#pragma once

#include "world_type.h"
#include "../../../config/world_config.h"
#include "../../block/block.h"

typedef struct {
  int minHeigth;
  int maxHeigth;
  float frequency;
  float amplitude;
  float baseTerrainHeight;
  float maxTerrainHeight;
} Default;

Default default_get_config();
Block default_get_block_by_y_level(Default config, float worldY);
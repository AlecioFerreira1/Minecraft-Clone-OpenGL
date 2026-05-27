#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "block.h"
#include "../../graphics/texture/atlas_tile.h"

typedef struct {
  AtlasTile top;
  AtlasTile bottom;
  AtlasTile left;
  AtlasTile right;
  AtlasTile front;
  AtlasTile back;
  bool transparent; 
  bool solid;
} BlockDefinition;  

extern const BlockDefinition REGISTERED_BLOCKS[BLOCK_COUNT];
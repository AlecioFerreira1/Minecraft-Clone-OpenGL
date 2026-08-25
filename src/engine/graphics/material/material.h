#pragma once

#include "../color/color.h"
#include "../texture/atlas_tile.h"

typedef struct {
  AtlasTile tile;
  Color color;
  bool animated;
} Material;
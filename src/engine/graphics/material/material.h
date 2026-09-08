#pragma once

#include "../color/color.h"
#include "../texture/atlas_tile.h"
#include "../geometry/render_mode.h"

#include <stdbool.h>

typedef struct {
  AtlasTile tile;
  Color color;
  bool animated;
  RenderMode renderMode;
  bool doubleSized;
} Material;
#pragma once

#include "../color/color.h"
#include "../texture/atlas_tile.h"
#include "../geometry/render_mode.h"

#include <stdbool.h>

#define MATERIAL_DEFAULT ((Material) { \
  .animated = false, \
  .color = (Color) {1.f, 1.f, 1.f, 1.f}, \
  .doubleSized = false, \
  .renderMode = RENDER_MODE_CUTOUT, \
  .tile = (AtlasTile) {.tile_x = 0, .tile_y = 0} \
}) \

typedef struct {
  AtlasTile tile;
  Color color;
  bool animated;
  RenderMode renderMode;
  bool doubleSized;
} Material;
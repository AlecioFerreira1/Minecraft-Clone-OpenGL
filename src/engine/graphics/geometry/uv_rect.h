#pragma once

#include "../texture/atlas_tile.h"
#include "../texture/texture.h"

typedef struct {
  float u;
  float v;
  float w;
  float h;
} UVrect;

UVrect uv_rect_convert(AtlasTile tile, TextureAtlas* texture);
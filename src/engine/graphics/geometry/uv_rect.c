#include "uv_rect.h"

UVrect uv_rect_convert(AtlasTile tile, TextureAtlas* texture) {
  return (UVrect) {
    (float) (tile.tile_x * texture->tileSize) / (float) texture->width, 
    (float) (tile.tile_y * texture->tileSize) / (float) texture->height,
    (float) texture->tileSize / (float) texture->width,
    (float) texture->tileSize / (float) texture->height
  };
}
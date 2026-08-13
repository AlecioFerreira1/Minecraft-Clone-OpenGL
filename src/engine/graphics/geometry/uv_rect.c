#include "uv_rect.h"

UVrect uv_rect_convert(AtlasTile tile, TextureAtlas *textureAtlas) {
  return (UVrect) {
    (float) (tile.tile_x * textureAtlas->tileSize) / (float) textureAtlas->texture->width, 
    (float) (tile.tile_y * textureAtlas->tileSize) / (float) textureAtlas->texture->height,
    (float) textureAtlas->tileSize / (float) textureAtlas->texture->width,
    (float) textureAtlas->tileSize / (float) textureAtlas->texture->height
  };
}
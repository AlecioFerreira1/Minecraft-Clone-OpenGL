#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "block.h"
#include "face.h"
#include "../../graphics/texture/atlas_tile.h"
#include "../../graphics/texture/texture.h"
#include "../../graphics/geometry/uv_rect.h"
#include "../../math/vec3.h"

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

UVrect block_registry_get_uv_rect(Block block, Face face, TextureAtlas *textures);

extern const BlockDefinition REGISTERED_BLOCKS[BLOCK_COUNT];
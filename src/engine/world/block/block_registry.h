#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "block.h"
#include "face.h"
#include "../../graphics/material/material.h"
#include "../../graphics/texture/texture.h"

typedef struct {
  Material top;
  Material bottom;
  Material left;
  Material right;
  Material front;
  Material back;
  bool transparent; 
  bool solid;
} BlockDefinition;

Material block_registry_get_material(Block block, Face face, TextureAtlas *textures);

extern const BlockDefinition REGISTERED_BLOCKS[BLOCK_COUNT];
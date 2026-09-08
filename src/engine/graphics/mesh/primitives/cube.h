#pragma once

#include "../mesh.h"
#include "../../color/color.h"
#include "../../geometry/quad.h"
#include "../../material/material.h"

typedef struct {
  Material top;
  Material bottom;
  Material left;
  Material right;
  Material front;
  Material back;
  TextureAtlas *textures;
} CubeMaterial;

Mesh *cube_create(Vec3 center, float size, CubeMaterial cubeMaterial);
// static Vector 
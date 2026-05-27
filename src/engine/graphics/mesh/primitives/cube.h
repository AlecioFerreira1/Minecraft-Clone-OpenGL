#pragma once

#include "../mesh.h"
#include "../../color/color.h"
#include "../../geometry/quad.h"
#include "../../geometry/uv_rect.h"

typedef struct {
  UVrect top;
  UVrect bottom;
  UVrect left;
  UVrect right;
  UVrect front;
  UVrect back;
} CubeUVSet;

Mesh* cube_create(float size, CubeUVSet uvSet);
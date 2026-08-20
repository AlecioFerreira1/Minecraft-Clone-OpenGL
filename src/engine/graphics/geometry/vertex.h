#pragma once

#include "../../math/vec2.h"
#include "../../math/vec3.h"
#include "uv_rect.h"
#include "../color/color.h"

typedef struct {
  Vec3 position;
  Color color;
  Vec3 normal;
  Vec2 local_uv;
  Vec2 tile_uv;
} Vertex;

Vertex vertex_create(Vec3 position, Color color, Vec3 normal, Vec2 local_uv, Vec2 tile_uv);
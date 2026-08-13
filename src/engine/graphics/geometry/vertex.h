#pragma once

#include "../../math/vec2.h"
#include "../../math/vec3.h"
#include "uv_rect.h"

typedef struct {
  Vec3 position;
  Vec3 normal;
  Vec2 uv;
} Vertex;

Vertex vertex_create(Vec3 position, Vec3 normal, Vec2 uv);
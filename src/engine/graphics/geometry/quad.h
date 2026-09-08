#pragma once

#include <stdlib.h>
#include <string.h>

#include "../../../data_structures/vector.h"
#include "../../math/vec3.h"
#include "../../math/vec2.h"
#include "../color/color.h"
#include "uv_rect.h"
#include "vertex.h"

Vector quad_gen_vertices(Vec3 pos, float width, float height, Color color, Vec3 normal, UVrect rect, bool reverse_winding);
static void push_vertex(Vector *vertices, Vec3 position, Color color, Vec3 normal, Vec2 local_uv, Vec2 tile_uv);

static void build_triangles_clockwise_from_bottom_left(
  Vector *vertices, Vec3 v0, Vec3 v1, Vec3 v2, Vec3 v3, Color color, Vec3 normal, 
  UVrect rect, Vec2 topLeft, Vec2 topRight, Vec2 bottomLeft, Vec2 bottomRight
);

static void build_triangles_counter_clockwise_from_top_right(
  Vector *vertices, Vec3 v0, Vec3 v1, Vec3 v2, Vec3 v3, Color color, Vec3 normal, 
  UVrect rect, Vec2 topLeft, Vec2 topRight, Vec2 bottomLeft, Vec2 bottomRight
);
#pragma once

#include <stdlib.h>
#include <string.h>

#include "../../../data_structures/vector.h"
#include "../../math/vec3.h"
#include "../../math/vec2.h"
#include "../color/color.h"
#include "uv_rect.h"
#include "vertex.h"

Vector quad_gen_vertices(Vec3 pos, float width, float height, Color color, Vec3 normal, UVrect rect);
static void push_vertex(Vector *vertices, Vec3 position, Color color, Vec3 normal, Vec2 local_uv, Vec2 tile_uv);
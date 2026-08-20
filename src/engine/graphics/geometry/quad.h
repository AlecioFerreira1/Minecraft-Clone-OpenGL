#pragma once

#include <stdlib.h>
#include <string.h>

#include "../../../data_structures/vector.h"
#include "../../math/vec3.h"
#include "../../math/vec2.h"
#include "uv_rect.h"
#include "vertex.h"

Vector quad_gen_vertices(Vec3 pos, float width, float height, Vec3 normal, UVrect rect);
static void push_vertex(Vector *vertices, Vec3 position, Vec3 normal, float u, float v);
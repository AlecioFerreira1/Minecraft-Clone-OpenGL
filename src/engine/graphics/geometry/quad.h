#pragma once

#include <stdlib.h>
#include <string.h>

#include "../../math/vec3.h"
#include "../../math/vec2.h"
#include "uv_rect.h"

float* quad_gen_vertices(Vec3 pos, float width, float height, Vec3 plane, UVrect rect);
static void push_vertex(float* vertex, int* i, Vec3 value, float u, float v);
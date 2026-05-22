#pragma once

#include <stdlib.h>
#include <string.h>

#include "../../math/vec3.h"
#include "../color/color.h"

float* quad_gen_vertices(float width, float height, Vec3 plane, Color color);
static void push_vertex(float* v, int* i, Vec3 value, Color c);
#pragma once

#include <stdlib.h>
#include <string.h>

#include "../math/vec3.h"
#include "../graphics/color/color.h"

float* vertices_quad(float width, float height, Vec3 plane, Vec3 pos, Color color);
static void push_vertex(float* v, int* i, Vec3 value, Color c);
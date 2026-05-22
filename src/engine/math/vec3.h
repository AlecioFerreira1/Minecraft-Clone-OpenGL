#pragma once

#include <math.h>

typedef struct {
  float x;
  float y;
  float z;
} Vec3;

Vec3 vec3_sum(Vec3 v0, Vec3 v1);
Vec3 vec3_sub(Vec3 v0, Vec3 v1);
Vec3 vec3_scale(Vec3 v, float s);
float vec3_lenght(Vec3 v);
Vec3 vec3_normalize(Vec3 v);
float vec3_dot(Vec3 v0, Vec3 v1);
Vec3 vec3_cross(Vec3 v0, Vec3 v1);
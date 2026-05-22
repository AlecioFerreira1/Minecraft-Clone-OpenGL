#include "quad.h"

float* quad_gen_vertices(float width, float height, Vec3 axis, Color color) {
  float* vertices = (float*) calloc(36, sizeof(float));
  int index = 0;

  Vec3 v0, v1, v2, v3;
  
  if(axis.z == 1 || axis.z == -1){
    v0 = (Vec3){-(width / 2), -(height / 2), axis.z * (width / 2)};
    v1 = (Vec3){(width / 2), -(height / 2), axis.z * (width / 2)};
    v2 = (Vec3){(width / 2), (height / 2), axis.z * (width / 2)};
    v3 = (Vec3){-(width / 2), (height / 2), axis.z * (width / 2)};
  }

  else if(axis.y == 1 || axis.y == -1){
    v0 = (Vec3){-(width / 2), axis.y * (width / 2), -(height / 2)};
    v1 = (Vec3){(width / 2), axis.y * (width / 2), -(height / 2)};
    v2 = (Vec3){(width / 2), axis.y * (width / 2), (height / 2)};
    v3 = (Vec3){-(width / 2), axis.y * (width / 2), (height / 2)};
  }

  else if(axis.x == 1 || axis.x == -1){
    v0 = (Vec3){axis.x * (width / 2), -(width / 2), -(height / 2)};
    v1 = (Vec3){axis.x * (width / 2), (width / 2), -(height / 2)};
    v2 = (Vec3){axis.x * (width / 2), (width / 2), (height / 2)};
    v3 = (Vec3){axis.x * (width / 2), -(width / 2), (height / 2)};
  }

  push_vertex(vertices, &index, v0, color);
  push_vertex(vertices, &index, v1, color);
  push_vertex(vertices, &index, v2, color);

  push_vertex(vertices, &index, v2, color);
  push_vertex(vertices, &index, v3, color);
  push_vertex(vertices, &index, v0, color);

  return vertices;  
}

static void push_vertex(float* v, int* i, Vec3 value, Color c) {
  v[(*i)++] = value.x;
  v[(*i)++] = value.y;
  v[(*i)++] = value.z;
  v[(*i)++] = c.r;
  v[(*i)++] = c.g;
  v[(*i)++] = c.b;
}
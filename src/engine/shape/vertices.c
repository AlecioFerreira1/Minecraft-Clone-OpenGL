#include "vertices.h"

float* vertices_quad(float width, float height, Vec3 plane, Vec3 pos, Color color) {
  float* vertices = (float*) calloc(36, sizeof(float));
  int index = 0;

  Vec3 v0, v1, v2, v3;
  
  if(plane.x == 1 && plane.y == 1){
    v0 = (Vec3){pos.x - (width / 2), pos.y - (height / 2), pos.z};
    v1 = (Vec3){pos.x + (width / 2), pos.y - (height / 2), pos.z};
    v2 = (Vec3){pos.x + (width / 2), pos.y + (height / 2), pos.z};
    v3 = (Vec3){pos.x - (width / 2), pos.y + (height / 2), pos.z};
  }

  else if(plane.x == 1 && plane.z == 1){
    v0 = (Vec3){pos.x - (width / 2), pos.y, pos.z - (height / 2)};
    v1 = (Vec3){pos.x + (width / 2), pos.y, pos.z - (height / 2)};
    v2 = (Vec3){pos.x + (width / 2), pos.y, pos.z + (height / 2)};
    v3 = (Vec3){pos.x - (width / 2), pos.y, pos.z + (height / 2)};
  }

  else if(plane.y == 1 && plane.z == 1){
    v0 = (Vec3){pos.x, pos.y - (width / 2), pos.z - (height / 2)};
    v1 = (Vec3){pos.x, pos.y + (width / 2), pos.z - (height / 2)};
    v2 = (Vec3){pos.x, pos.y + (width / 2), pos.z + (height / 2)};
    v3 = (Vec3){pos.x, pos.y - (width / 2), pos.z + (height / 2)};
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
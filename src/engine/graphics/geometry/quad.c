#include "quad.h"

float* quad_gen_vertices(Vec3 pos, float width, float height, Vec3 axis, UVrect rect) {
  float* vertices = (float*) calloc(30, sizeof(float));
  int index = 0;

  Vec2 topLeft = {0.f, 0.f};
  Vec2 topRight = {0.f, 0.f};
  Vec2 bottomLeft = {0.f, 0.f}; 
  Vec2 bottomRight = {0.f, 0.f};

  Vec3 v0, v1, v2, v3;
  
  if(axis.z == 1 || axis.z == -1){
    v0 = (Vec3){pos.x - (width / 2), pos.y - (height / 2), pos.z + (axis.z * (width / 2))};
    v1 = (Vec3){pos.x + (width / 2), pos.y - (height / 2), pos.z + (axis.z * (width / 2))};
    v2 = (Vec3){pos.x + (width / 2), pos.y + (height / 2), pos.z + (axis.z * (width / 2))};
    v3 = (Vec3){pos.x - (width / 2), pos.y + (height / 2), pos.z + (axis.z * (width / 2))};
    topLeft = (Vec2){.x = rect.u, .y = rect.v}; 
    topRight = (Vec2){.x = rect.u + rect.w, .y = rect.v};  
    bottomLeft = (Vec2){.x = rect.u, .y = rect.v + rect.h};  
    bottomRight = (Vec2){.x = rect.u + rect.w, .y = rect.v + rect.h}; 
  }

  else if(axis.y == 1 || axis.y == -1){
    v0 = (Vec3){pos.x - (width / 2), pos.y + (axis.y * (width / 2)), pos.z - (height / 2)};
    v1 = (Vec3){pos.x + (width / 2), pos.y + (axis.y * (width / 2)), pos.z - (height / 2)};
    v2 = (Vec3){pos.x + (width / 2), pos.y + (axis.y * (width / 2)), pos.z + (height / 2)};
    v3 = (Vec3){pos.x - (width / 2), pos.y + (axis.y * (width / 2)), pos.z + (height / 2)};
    topLeft = (Vec2){.x = rect.u + rect.w, .y = rect.v + rect.h}; 
    topRight = (Vec2){.x = rect.u, .y = rect.v + rect.h};  
    bottomLeft = (Vec2){.x = rect.u + rect.w, .y = rect.v};  
    bottomRight = (Vec2){.x = rect.u, .y = rect.v}; 
  }

  else if(axis.x == 1 || axis.x == -1){
    v0 = (Vec3){pos.x + (axis.x * (width / 2)), pos.y - (width / 2), pos.z - (height / 2)};
    v1 = (Vec3){pos.x + (axis.x * (width / 2)), pos.y + (width / 2), pos.z - (height / 2)};
    v2 = (Vec3){pos.x + (axis.x * (width / 2)), pos.y + (width / 2), pos.z + (height / 2)};
    v3 = (Vec3){pos.x + (axis.x * (width / 2)), pos.y - (width / 2), pos.z + (height / 2)};
    topLeft = (Vec2){.x = rect.u, .y = rect.v + rect.h};
    topRight = (Vec2){.x = rect.u, .y = rect.v};
    bottomLeft = (Vec2){.x = rect.u + rect.w, .y = rect.v + rect.h}; 
    bottomRight = (Vec2){.x = rect.u + rect.w, .y = rect.v};
  } 

  if(axis.y == -1 || axis.x == 1 || axis.z == 1){
    push_vertex(vertices, &index, v0, bottomLeft.x, bottomLeft.y);
    push_vertex(vertices, &index, v1, bottomRight.x, bottomRight.y);
    push_vertex(vertices, &index, v2, topRight.x, topRight.y);

    push_vertex(vertices, &index, v2, topRight.x, topRight.y);
    push_vertex(vertices, &index, v3, topLeft.x, topLeft.y);
    push_vertex(vertices, &index, v0, bottomLeft.x, bottomLeft.y);
  }

  else if(axis.y == 1 || axis.x == -1 || axis.z == -1){
    push_vertex(vertices, &index, v2, topRight.x, topRight.y);
    push_vertex(vertices, &index, v1, bottomRight.x, bottomRight.y);
    push_vertex(vertices, &index, v0, bottomLeft.x, bottomLeft.y);

    push_vertex(vertices, &index, v0, bottomLeft.x, bottomLeft.y);
    push_vertex(vertices, &index, v3, topLeft.x, topLeft.y);
    push_vertex(vertices, &index, v2, topRight.x, topRight.y);
  }

  return vertices;  
}

static void push_vertex(float* vertex, int* i, Vec3 value, float u, float v) {
  vertex[(*i)++] = value.x;
  vertex[(*i)++] = value.y;
  vertex[(*i)++] = value.z;
  vertex[(*i)++] = u;
  vertex[(*i)++] = v;
}

/**
 * 
  V3--------V2
  |	        |
  |         |
  V0--------V1

  coordenadas de textura: (u, v, w, h)

  V3 = (0, 1) -> uv correspondente: (u, v) 
  V0 = (0, 0) -> uv correspondente: (u, v + h)
  V2 = (1, 1) -> uv correspondente: (u + w, v)
  V1 = (1, 0) -> uv correspondente: (u + w, v + h)

  para z funciona a fórmula acima, para y rotaciona em 90 graus no eixo x
  e para x rotaciona em 90 graus no eixo y

  para y fica:

  V3 = (0, 1) -> uv correspondente: (u + w, v + h) 
  V0 = (0, 0) -> uv correspondente: (u + w, v)
  V2 = (1, 1) -> uv correspondente: (u, v + h)
  V1 = (1, 0) -> uv correspondente: (u, v)

  para x fica:

  V3 = (0, 1) -> uv correspondente: (u, v + h) 
  V0 = (0, 0) -> uv correspondente: (u, v)
  V2 = (1, 1) -> uv correspondente: (u + w, v + h)
  V1 = (1, 0) -> uv correspondente: (u + w, v)
 */
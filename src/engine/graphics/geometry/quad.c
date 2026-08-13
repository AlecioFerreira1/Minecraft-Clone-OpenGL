#include "quad.h"

Vector quad_gen_vertices(Vec3 pos, float width, float height, float depth, Vec3 normal, UVrect rect) {
  Vector vertices = vector_create(30, sizeof(Vertex));

  Vec2 topLeft = {0.f, 0.f};
  Vec2 topRight = {0.f, 0.f};
  Vec2 bottomLeft = {0.f, 0.f}; 
  Vec2 bottomRight = {0.f, 0.f};

  Vec3 v0, v1, v2, v3;
  
  if(normal.z == 1 || normal.z == -1){
    v0 = (Vec3){pos.x - (width / 2), pos.y - (height / 2), pos.z + (normal.z * (depth / 2))};
    v1 = (Vec3){pos.x + (width / 2), pos.y - (height / 2), pos.z + (normal.z * (depth / 2))};
    v2 = (Vec3){pos.x + (width / 2), pos.y + (height / 2), pos.z + (normal.z * (depth / 2))};
    v3 = (Vec3){pos.x - (width / 2), pos.y + (height / 2), pos.z + (normal.z * (depth / 2))};
    topLeft = (Vec2){.x = rect.u, .y = rect.v}; 
    topRight = (Vec2){.x = rect.u + rect.w, .y = rect.v};  
    bottomLeft = (Vec2){.x = rect.u, .y = rect.v + rect.h};  
    bottomRight = (Vec2){.x = rect.u + rect.w, .y = rect.v + rect.h}; 
  }

  else if(normal.y == 1 || normal.y == -1){
    v0 = (Vec3){pos.x - (width / 2), pos.y + (normal.y * (depth / 2)), pos.z - (height / 2)};
    v1 = (Vec3){pos.x + (width / 2), pos.y + (normal.y * (depth / 2)), pos.z - (height / 2)};
    v2 = (Vec3){pos.x + (width / 2), pos.y + (normal.y * (depth / 2)), pos.z + (height / 2)};
    v3 = (Vec3){pos.x - (width / 2), pos.y + (normal.y * (depth / 2)), pos.z + (height / 2)};
    topLeft = (Vec2){.x = rect.u + rect.w, .y = rect.v + rect.h}; 
    topRight = (Vec2){.x = rect.u, .y = rect.v + rect.h};  
    bottomLeft = (Vec2){.x = rect.u + rect.w, .y = rect.v};  
    bottomRight = (Vec2){.x = rect.u, .y = rect.v}; 
  }

  else if(normal.x == 1 || normal.x == -1){
    v0 = (Vec3){pos.x + (normal.x * (depth / 2)), pos.y - (width / 2), pos.z - (height / 2)};
    v1 = (Vec3){pos.x + (normal.x * (depth / 2)), pos.y + (width / 2), pos.z - (height / 2)};
    v2 = (Vec3){pos.x + (normal.x * (depth / 2)), pos.y + (width / 2), pos.z + (height / 2)};
    v3 = (Vec3){pos.x + (normal.x * (depth / 2)), pos.y - (width / 2), pos.z + (height / 2)};
    topLeft = (Vec2){.x = rect.u, .y = rect.v + rect.h};
    topRight = (Vec2){.x = rect.u, .y = rect.v};
    bottomLeft = (Vec2){.x = rect.u + rect.w, .y = rect.v + rect.h}; 
    bottomRight = (Vec2){.x = rect.u + rect.w, .y = rect.v};
  } 

  if(normal.y == -1 || normal.x == 1 || normal.z == 1){
    push_vertex(&vertices, v0, normal, bottomLeft.x, bottomLeft.y);
    push_vertex(&vertices, v1, normal, bottomRight.x, bottomRight.y);
    push_vertex(&vertices, v2, normal, topRight.x, topRight.y);

    push_vertex(&vertices, v2, normal, topRight.x, topRight.y);
    push_vertex(&vertices, v3, normal, topLeft.x, topLeft.y);
    push_vertex(&vertices, v0, normal, bottomLeft.x, bottomLeft.y);
  }

  else if(normal.y == 1 || normal.x == -1 || normal.z == -1){
    push_vertex(&vertices, v2, normal, topRight.x, topRight.y);
    push_vertex(&vertices, v1, normal, bottomRight.x, bottomRight.y);
    push_vertex(&vertices, v0, normal, bottomLeft.x, bottomLeft.y);

    push_vertex(&vertices, v0, normal, bottomLeft.x, bottomLeft.y);
    push_vertex(&vertices, v3, normal, topLeft.x, topLeft.y);
    push_vertex(&vertices, v2, normal, topRight.x, topRight.y);
  }

  return vertices;  
}

static void push_vertex(Vector *vertices, Vec3 position, Vec3 normal, float u, float v) {
  Vertex vertex = vertex_create(position, normal, (Vec2) {u, v});
  vector_push_back(vertices, &vertex);
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
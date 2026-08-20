#include "quad.h"

Vector quad_gen_vertices(Vec3 pos, float width, float height, Vec3 normal, UVrect rect) {
  Vector vertices = vector_create(6, sizeof(Vertex));

  Vec2 topLeft = {0.f, 0.f};
  Vec2 topRight = {0.f, 0.f};
  Vec2 bottomLeft = {0.f, 0.f}; 
  Vec2 bottomRight = {0.f, 0.f};

  Vec3 v0, v1, v2, v3;
  
  if(normal.z != 0.f){
    v0 = (Vec3){pos.x, pos.y, pos.z};
    v1 = (Vec3){pos.x + width, pos.y, pos.z};
    v2 = (Vec3){pos.x + width, pos.y + height, pos.z};
    v3 = (Vec3){pos.x, pos.y + height, pos.z};
    topLeft = (Vec2){.x = rect.u, .y = rect.v}; 
    topRight = (Vec2){.x = rect.u + rect.w, .y = rect.v};  
    bottomLeft = (Vec2){.x = rect.u, .y = rect.v + rect.h};  
    bottomRight = (Vec2){.x = rect.u + rect.w, .y = rect.v + rect.h}; 
  }

  else if(normal.y != 0.f){
    v0 = (Vec3){pos.x, pos.y, pos.z};
    v1 = (Vec3){pos.x + width, pos.y, pos.z};
    v2 = (Vec3){pos.x + width, pos.y, pos.z + height};
    v3 = (Vec3){pos.x, pos.y, pos.z + height};
    topLeft = (Vec2){.x = rect.u + rect.w, .y = rect.v + rect.h}; 
    topRight = (Vec2){.x = rect.u, .y = rect.v + rect.h};  
    bottomLeft = (Vec2){.x = rect.u + rect.w, .y = rect.v};  
    bottomRight = (Vec2){.x = rect.u, .y = rect.v}; 
  }

  else if(normal.x != 0.f){
    v0 = (Vec3){pos.x, pos.y, pos.z};
    v1 = (Vec3){pos.x, pos.y + height, pos.z};
    v2 = (Vec3){pos.x, pos.y + height, pos.z + width};
    v3 = (Vec3){pos.x, pos.y, pos.z + width};
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
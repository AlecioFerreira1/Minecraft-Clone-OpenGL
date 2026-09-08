#include "quad.h"

Vector quad_gen_vertices(Vec3 pos, float width, float height, Color color, Vec3 normal, UVrect rect, bool reverse_winding) {
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
    topLeft = (Vec2){0.f, 0.f}; 
    topRight = (Vec2){width, 0.f};  
    bottomLeft = (Vec2){0.f, height};  
    bottomRight = (Vec2){width, height}; 
  }

  else if(normal.y != 0.f){
    v0 = (Vec3){pos.x, pos.y, pos.z};
    v1 = (Vec3){pos.x + width, pos.y, pos.z};
    v2 = (Vec3){pos.x + width, pos.y, pos.z + height};
    v3 = (Vec3){pos.x, pos.y, pos.z + height};
    topLeft = (Vec2){width, height}; 
    topRight = (Vec2){0.f, height};  
    bottomLeft = (Vec2){width, 0.f};  
    bottomRight = (Vec2){0.f, 0.f}; 
  }

  else if(normal.x != 0.f){
    v0 = (Vec3){pos.x, pos.y, pos.z};
    v1 = (Vec3){pos.x, pos.y + height, pos.z};
    v2 = (Vec3){pos.x, pos.y + height, pos.z + width};
    v3 = (Vec3){pos.x, pos.y, pos.z + width};
    topLeft = (Vec2){0.f, height};
    topRight = (Vec2){0.f, 0.f};
    bottomLeft = (Vec2){width, height}; 
    bottomRight = (Vec2){width, 0.f};
  } 

  if(normal.y == -1 || normal.x == 1 || normal.z == 1){
    if(reverse_winding) {
      normal = vec3_scale(normal, -1);

      build_triangles_counter_clockwise_from_top_right(
        &vertices, v0, v1, v2, v3, color, normal, rect, topLeft, topRight, bottomLeft, bottomRight
      );
    }

    else {
      build_triangles_clockwise_from_bottom_left(
        &vertices, v0, v1, v2, v3, color, normal, rect, topLeft, topRight, bottomLeft, bottomRight
      );
    }
  }

  else if(normal.y == 1 || normal.x == -1 || normal.z == -1){
    if(reverse_winding) {
      normal = vec3_scale(normal, -1);

      build_triangles_clockwise_from_bottom_left(
        &vertices, v0, v1, v2, v3, color, normal, rect, topLeft, topRight, bottomLeft, bottomRight
      );
    } 

    else {
      build_triangles_counter_clockwise_from_top_right(
        &vertices, v0, v1, v2, v3, color, normal, rect, topLeft, topRight, bottomLeft, bottomRight
      ); 
    }
  }

  return vertices;  
}

static void push_vertex(Vector *vertices, Vec3 position, Color color, Vec3 normal, Vec2 local_uv, Vec2 tile_uv) {
  Vertex vertex = vertex_create(position, color, normal, local_uv, tile_uv);
  vector_push_back(vertices, &vertex);
}

static void build_triangles_clockwise_from_bottom_left(
  Vector *vertices, Vec3 v0, Vec3 v1, Vec3 v2, Vec3 v3, Color color, Vec3 normal, 
  UVrect rect, Vec2 topLeft, Vec2 topRight, Vec2 bottomLeft, Vec2 bottomRight
) {
  push_vertex(vertices, v0, color, normal, bottomLeft, (Vec2){rect.u, rect.v});
  push_vertex(vertices, v1, color, normal, bottomRight, (Vec2){rect.u, rect.v});
  push_vertex(vertices, v2, color, normal, topRight, (Vec2){rect.u, rect.v});

  push_vertex(vertices, v2, color, normal, topRight, (Vec2){rect.u, rect.v});
  push_vertex(vertices, v3, color, normal, topLeft, (Vec2){rect.u, rect.v});
  push_vertex(vertices, v0, color, normal, bottomLeft, (Vec2){rect.u, rect.v});
}

static void build_triangles_counter_clockwise_from_top_right(
  Vector *vertices, Vec3 v0, Vec3 v1, Vec3 v2, Vec3 v3, Color color, Vec3 normal, 
  UVrect rect, Vec2 topLeft, Vec2 topRight, Vec2 bottomLeft, Vec2 bottomRight
) {
  push_vertex(vertices, v2, color, normal, topRight, (Vec2){rect.u, rect.v});
  push_vertex(vertices, v1, color, normal, bottomRight, (Vec2){rect.u, rect.v});
  push_vertex(vertices, v0, color, normal, bottomLeft, (Vec2){rect.u, rect.v});

  push_vertex(vertices, v0, color, normal, bottomLeft, (Vec2){rect.u, rect.v});
  push_vertex(vertices, v3, color, normal, topLeft, (Vec2){rect.u, rect.v});
  push_vertex(vertices, v2, color, normal, topRight, (Vec2){rect.u, rect.v});
}
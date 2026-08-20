#include "vertex.h"

Vertex vertex_create(Vec3 position, Color color, Vec3 normal, Vec2 local_uv, Vec2 tile_uv) {
  Vertex vertex;

  vertex.position = position;
  vertex.color = color;
  vertex.normal = normal;
  vertex.local_uv = local_uv;
  vertex.tile_uv = tile_uv; 

  return vertex;
}
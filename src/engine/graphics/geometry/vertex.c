#include "vertex.h"

Vertex vertex_create(Vec3 position, Vec3 normal, Vec2 uv) {
  Vertex vertex;

  vertex.position = position;
  vertex.normal = normal;
  vertex.uv = uv;

  return vertex;
}
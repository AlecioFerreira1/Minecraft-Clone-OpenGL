#include "cube.h"

Mesh *cube_create(Vec3 center, float size, CubeUVSet uvSet) {
  Vector vertices = vector_create(180, sizeof(Vertex));
  Vec3 min = vec3_sub(center, (Vec3) {size / 2, size / 2, size / 2});
  Vec3 max = vec3_sum(center, (Vec3) {size / 2, size / 2, size / 2});

  Vector faceUp = quad_gen_vertices((Vec3) {min.x, max.y, min.z}, size, size, (Vec3){0, 1, 0}, uvSet.top);
  Vector faceBottom = quad_gen_vertices((Vec3) {min.x, min.y, min.z}, size, size, (Vec3){0, -1, 0}, uvSet.bottom);
  Vector faceLeft = quad_gen_vertices((Vec3) {min.x, min.y, min.z}, size, size, (Vec3){-1, 0, 0}, uvSet.left);
  Vector faceRight = quad_gen_vertices((Vec3) {max.x, min.y, min.z}, size, size, (Vec3){1, 0, 0}, uvSet.right);
  Vector faceFront = quad_gen_vertices((Vec3) {min.x, min.y, min.z}, size, size, (Vec3){0, 0, -1}, uvSet.front);
  Vector faceBack = quad_gen_vertices((Vec3) {min.x, min.y, max.z}, size, size, (Vec3){0, 0, 1}, uvSet.back);

  vector_append_many(&vertices, &faceUp);
  vector_append_many(&vertices, &faceBottom);
  vector_append_many(&vertices, &faceLeft);
  vector_append_many(&vertices, &faceRight);
  vector_append_many(&vertices, &faceFront);
  vector_append_many(&vertices, &faceBack);

  vector_destroy(&faceUp);
  vector_destroy(&faceBottom);
  vector_destroy(&faceLeft);
  vector_destroy(&faceRight);
  vector_destroy(&faceFront);
  vector_destroy(&faceBack);

  Mesh *mesh = mesh_create((Vertex *) vertices.data, vertices.size, GL_STATIC_DRAW);

  vector_destroy(&vertices);

  return mesh;
}
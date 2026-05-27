#include "cube.h"

Mesh* cube_create(float size, CubeUVSet uvSet) {
  float vertices[180];
  
  float* faceUp = quad_gen_vertices(size, size, (Vec3){0, 1, 0}, uvSet.top);
  float* faceBottom = quad_gen_vertices(size, size, (Vec3){0, -1, 0}, uvSet.bottom);

  float* faceLeft = quad_gen_vertices(size, size, (Vec3){-1, 0, 0}, uvSet.left);
  float* faceRight = quad_gen_vertices(size, size, (Vec3){1, 0, 0}, uvSet.right);

  float* faceFront = quad_gen_vertices(size, size, (Vec3){0, 0, -1}, uvSet.front);
  float* faceBack = quad_gen_vertices(size, size, (Vec3){0, 0, 1}, uvSet.back);

  memcpy(vertices, faceUp, 30 * sizeof(float));
  memcpy(vertices + 30, faceBottom, 30 * sizeof(float));
  memcpy(vertices + 60, faceLeft, 30 * sizeof(float));
  memcpy(vertices + 90, faceRight, 30 * sizeof(float));
  memcpy(vertices + 120, faceFront, 30 * sizeof(float));
  memcpy(vertices + 150, faceBack, 30 * sizeof(float));

  free(faceUp);
  free(faceBottom);
  free(faceLeft);
  free(faceRight);
  free(faceFront);
  free(faceBack);

  Mesh* mesh = mesh_create(vertices, 36, 5 * sizeof(float), GL_STATIC_DRAW);

  glVertexAttribPointer(ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, mesh->stride, (void *)0);
  glEnableVertexAttribArray(ATTR_POSITION);
  glVertexAttribPointer(ATTR_UV, 2, GL_FLOAT, GL_FALSE, mesh->stride, (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(ATTR_UV);

  return mesh;
}
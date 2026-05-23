#include "cube.h"

Mesh cube_create(float size, Color (*color)[6]) {
  float vertices[216];
  
  float* faceUp = quad_gen_vertices(size, size, (Vec3){0, 1, 0}, (*color)[0]);
  float* faceBottom = quad_gen_vertices(size, size, (Vec3){0, -1, 0}, (*color)[5]);

  float* faceSide1 = quad_gen_vertices(size, size, (Vec3){1, 0, 0}, (*color)[1]);
  float* faceSide2 = quad_gen_vertices(size, size, (Vec3){-1, 0, 0}, (*color)[2]);

  float* faceSide3 = quad_gen_vertices(size, size, (Vec3){0, 0, 1}, (*color)[3]);
  float* faceSide4 = quad_gen_vertices(size, size, (Vec3){0, 0, -1}, (*color)[4]);

  memcpy(vertices, faceUp, 36 * sizeof(float));
  memcpy(vertices + 36, faceBottom, 36 * sizeof(float));
  memcpy(vertices + 72, faceSide1, 36 * sizeof(float));
  memcpy(vertices + 108, faceSide2, 36 * sizeof(float));
  memcpy(vertices + 144, faceSide3, 36 * sizeof(float));
  memcpy(vertices + 180, faceSide4, 36 * sizeof(float));

  free(faceUp);
  free(faceBottom);
  free(faceSide1);
  free(faceSide2);
  free(faceSide3);
  free(faceSide4);

  Mesh mesh = mesh_create(vertices, 36, 6 * sizeof(float), GL_STATIC_DRAW);

  glVertexAttribPointer(ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, mesh.stride, (void *)0);
  glEnableVertexAttribArray(ATTR_POSITION);
  glVertexAttribPointer(ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, mesh.stride, (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(ATTR_COLOR);

  return mesh;
}
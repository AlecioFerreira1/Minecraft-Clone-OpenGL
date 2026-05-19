#include "cube.h"


#include <stdio.h>

Mesh cube_create(float size, Vec3 pos, Color (*color)[6]) {
  float vertices[216];
  int index = 0;
  Color* colors = *color;

  float* faceUp = vertices_quad(size, size, (Vec3){1, 1, 0}, (Vec3){pos.x, pos.y, pos.z - (size / 2)}, (*color)[0]);
  float* faceBottom = vertices_quad(size, size, (Vec3){1, 1, 0}, (Vec3){pos.x, pos.y, pos.z + (size / 2)}, (*color)[6]);

  float* faceSide1 = vertices_quad(size, size, (Vec3){1, 0, 1}, (Vec3){pos.x, pos.y - (size / 2), pos.z}, (*color)[2]);
  float* faceSide2 = vertices_quad(size, size, (Vec3){1, 0, 1}, (Vec3){pos.x, pos.y + (size / 2), pos.z}, (*color)[3]);

  float* faceSide3 = vertices_quad(size, size, (Vec3){0, 1, 1}, (Vec3){pos.x - (size / 2), pos.y, pos.z}, (*color)[4]);
  float* faceSide4 = vertices_quad(size, size, (Vec3){0, 1, 1}, (Vec3){pos.x + (size / 2), pos.y, pos.z}, (*color)[5]);

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

  return mesh_create(vertices, 36, 6 * sizeof(float), GL_STATIC_DRAW);
}
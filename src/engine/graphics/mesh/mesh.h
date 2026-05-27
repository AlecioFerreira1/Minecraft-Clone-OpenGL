#pragma once

#include <glad/glad.h>
#include <stdlib.h>

typedef struct {
  GLuint VAO;
  GLuint VBO;
  unsigned int numVertices;
  size_t stride;
} Mesh;

typedef enum {
  ATTR_POSITION = 0,
  ATTR_COLOR = 1,
  ATTR_UV = 2,
  ATTR_NORMAL = 3
} VertexAttribute;

Mesh* mesh_create(float* vertices, int numVertices, size_t stride, GLenum usage);
void mesh_destroy(Mesh* mesh);
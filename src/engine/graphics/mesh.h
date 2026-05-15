#pragma once

#include <glad/glad.h>

typedef struct {
  GLuint VAO;
  GLuint VBO;
  unsigned int numVertices;
} Mesh;

Mesh mesh_create(float* vertices, int numVertices);
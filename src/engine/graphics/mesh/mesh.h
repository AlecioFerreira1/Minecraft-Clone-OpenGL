#pragma once

#include <glad/glad.h>
#include <stdlib.h>

#include "../../../data_structures/vector.h"
#include "../geometry/vertex.h"

typedef struct {
  GLuint VAO;
  GLuint VBO;
  size_t numVertices;
} Mesh;

enum VertexAttribute {
  ATTR_POSITION = 0,
  ATTR_COLOR = 1,
  ATTR_UV = 2,
  ATTR_NORMAL = 3
};

Mesh *mesh_create(const Vertex *vertices, size_t numVertices, GLenum usage);
void mesh_destroy(Mesh *mesh);
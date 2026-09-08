#pragma once

#include <glad/glad.h>
#include <stdlib.h>

#include "../../../data_structures/vector.h"
#include "../geometry/vertex.h"
#include "../geometry/render_mode.h"

typedef struct {
  size_t startIndex;
  size_t indexesCount;
  RenderMode renderMode;
} SubMesh;

typedef struct {
  GLuint VAO;
  GLuint VBO;
  size_t numVertices;
  Vector subMeshes;
 } Mesh;

enum VertexAttribute {
  ATTR_POSITION = 0,
  ATTR_COLOR = 1,
  ATTR_LOCAL_UV = 2,
  ATTR_NORMAL = 3,
  ATRR_TILE_UV = 4
};

Mesh *mesh_create(const Vertex *vertices, size_t numVertices, const Vector *subMeshes, GLenum usage);
void mesh_destroy(Mesh *mesh);
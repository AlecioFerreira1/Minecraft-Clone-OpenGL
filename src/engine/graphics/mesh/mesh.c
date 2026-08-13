#include "mesh.h"

Mesh *mesh_create(const Vertex *vertices, size_t numVertices, GLenum usage) {
  GLuint VAO, VBO;

  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vertex), vertices, usage);

  Mesh *mesh = malloc(sizeof(Mesh));
  *mesh = (Mesh) {VAO, VBO, numVertices};

  glVertexAttribPointer(ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
  glEnableVertexAttribArray(ATTR_POSITION);

  glVertexAttribPointer(ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
  glEnableVertexAttribArray(ATTR_NORMAL);

  glVertexAttribPointer(ATTR_UV, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uv));
  glEnableVertexAttribArray(ATTR_UV);

  return mesh;
}

void mesh_destroy(Mesh *mesh) {
  if(mesh != NULL) {
    glDeleteVertexArrays(1, &mesh->VAO);
    glDeleteBuffers(1, &mesh->VBO);
    free(mesh);
  }
}
#include "mesh.h"

Mesh* mesh_create(float* vertices, int numVertices, size_t stride, GLenum usage) {
  GLuint VAO, VBO;

  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, numVertices * stride, vertices, usage);

  Mesh* mesh = malloc(sizeof(Mesh));
  *mesh = (Mesh) {VAO, VBO, numVertices, stride};

  glVertexAttribPointer(ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, mesh->stride, (void *)0);
  glEnableVertexAttribArray(ATTR_POSITION);
  glVertexAttribPointer(ATTR_UV, 2, GL_FLOAT, GL_FALSE, mesh->stride, (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(ATTR_UV);

  return mesh;
}

void mesh_destroy(Mesh* mesh) {
  if(mesh != NULL) {
    glDeleteVertexArrays(1, &mesh->VAO);
    glDeleteBuffers(1, &mesh->VBO);
    free(mesh);
  }
}
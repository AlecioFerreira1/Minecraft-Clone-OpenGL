#include "renderer.h"

void renderer_init(Renderer* renderer, GLFWwindow* window) {
  GLuint shader = shader_create(
    "assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl"
  );

  renderer->window = window;
  renderer->shader = shader;
  renderer->locModel = glGetUniformLocation(renderer->shader, "model"); 
  renderer->locView = glGetUniformLocation(renderer->shader, "view");
}

void renderer_begin(Renderer* renderer) {
  glBindVertexArray(0);
  glClearColor(1.f, 1.f, 1.f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUseProgram(renderer->shader); 
}

void renderer_draw_mesh(Renderer* renderer, Mesh* mesh, Mat4 model) {
  glUniformMatrix4fv(renderer->locModel, 1, GL_FALSE, model.data);
  glBindVertexArray(mesh->VAO);
  glDrawArrays(GL_TRIANGLES, 0, mesh->numVertices);
}

void renderer_set_view(Renderer* renderer, Mat4 view) {
  glUniformMatrix4fv(renderer->locView, 1, GL_FALSE, view.data);
}

void renderer_end(Renderer* renderer) {
  glfwSwapBuffers(renderer->window);
}
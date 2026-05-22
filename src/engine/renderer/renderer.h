#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../graphics/mesh/mesh.h"
#include "../math/mat4.h"
#include "../graphics/shader/shader.h"

typedef struct {
  GLuint shader;
  GLFWwindow* window;
  GLint locModel;
  GLint locView;
} Renderer;

void renderer_init(Renderer* renderer, GLFWwindow* window);
void renderer_begin(Renderer* renderer);
void renderer_draw_mesh(Renderer* renderer, Mesh* mesh, Mat4 model);
void renderer_set_view(Renderer* renderer, Mat4 view);
void renderer_end(Renderer* renderer);
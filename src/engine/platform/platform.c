#include "platform.h"

void platform_setup_glfw() {
  if(!glfwInit()){
    printf("Erro ao iniciar GLFW.\n");
    exit(-1);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void platform_setup_glad() {
  if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
    printf("Erro ao inicializar Glad.\n");
    exit(-1);
  }
}

void platform_setup_OpenGL_configs(int width, int height) {
  glViewport(0, 0, width, height);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
}
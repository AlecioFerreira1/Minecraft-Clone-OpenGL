#include "window.h"

GLFWwindow* window_create(const char* title, int width, int height) {
  GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);

  if(window == NULL){
    printf("Erro ao criar a janela GLFW.\n");
    glfwTerminate();
    exit(-1);
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  return window;
}

void window_destroy() {
  glfwTerminate();
}

static void framebuffer_size_callback(GLFWwindow* window, int w, int h) {
  glViewport(0, 0, w, h);
}

float window_get_aspect_ratio(GLFWwindow* window) {
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);

  return (float) (width / height);
}
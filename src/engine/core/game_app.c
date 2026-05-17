#include "game_app.h"

#include <stdio.h>

void gameApp_init(GameApp* app) {
  platform_setup_glfw();

  app->window = window_create("Minecraft Clone OpenGL", 800, 600);

  platform_setup_glad();

  int width, height;

  glfwGetFramebufferSize(app->window, &width, &height);
  glViewport(0, 0, width, height);
}

void gameApp_run(GameApp* app) {
  float vertices[] = {
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    -0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
  };

  Mesh mesh = mesh_create(vertices, 3, 6 * sizeof(float), GL_STATIC_DRAW);
  
  glVertexAttribPointer(ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, mesh.stride, (void *)0);
  glEnableVertexAttribArray(ATTR_POSITION);

  glVertexAttribPointer(ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, mesh.stride, (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(ATTR_COLOR);

  glBindVertexArray(0);

  GLuint shader = shader_create(
    "assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl"
  );

  float x = 0.00f, y = 0.0f;
  int loc = glGetUniformLocation(shader, "offset");

  while(!glfwWindowShouldClose(app->window)) {
    glfwPollEvents();
    input_process_key(app->window);

    if(glfwGetKey(app->window, GLFW_KEY_A) == GLFW_PRESS){
      x -= 0.01f;
      printf("x: %f\n", x);
    }

    if(glfwGetKey(app->window, GLFW_KEY_D) == GLFW_PRESS){
      x += 0.01f;
      printf("x: %f\n", x);
    }

    if(glfwGetKey(app->window, GLFW_KEY_W) == GLFW_PRESS){
      y += 0.01f;
      printf("y: %f\n", x);
    }

    if(glfwGetKey(app->window, GLFW_KEY_S) == GLFW_PRESS){
      y -= 0.01f;
      printf("y: %f\n", x);
    }

    glClearColor(1.f, 1.f, 1.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader);
    glUniform3f(loc, x, y, 0.0f);

    glBindVertexArray(mesh.VAO);
    glDrawArrays(GL_TRIANGLES, 0, mesh.numVertices);

    glfwSwapBuffers(app->window);
  }
}

void gameApp_destroy(GameApp *app) {
  window_destroy();
}
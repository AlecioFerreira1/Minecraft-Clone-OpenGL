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
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f,
  };

  GLuint VBO, VAO;  

  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);

  GLuint shader = shader_create(
    "assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl"
  );

  while(!glfwWindowShouldClose(app->window)){
    glfwPollEvents();
    input_process_key(app->window);

    glClearColor(1.f, 1.f, 1.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(app->window);
  }
}

void gameApp_destroy(GameApp *app) {
  window_destroy();
}
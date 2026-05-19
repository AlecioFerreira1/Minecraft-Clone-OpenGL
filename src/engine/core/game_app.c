#include "game_app.h"

#include <stdio.h>
#include <math.h>

void gameApp_init(GameApp* app) {
  platform_setup_glfw();

  app->window = window_create("Minecraft Clone OpenGL", 900, 900);

  platform_setup_glad();

  int width, height;

  glfwGetFramebufferSize(app->window, &width, &height);
  glViewport(0, 0, width, height);
  glEnable(GL_DEPTH_TEST);
}

void gameApp_run(GameApp* app) {
  Color color[6] = {
    pallete[COLOR_RED], pallete[COLOR_GREEN], pallete[COLOR_ORANGE],
    pallete[COLOR_LIGHT_GREEN], pallete[COLOR_BLUE], pallete[COLOR_GRAY],  
  };

  Mesh mesh = cube_create(0.5f, (Vec3){0, 0, 0}, &color);

  Mesh cubes[49];
  int indexCubes = 0;

  for(int i = 0; i < 7; ++i){
    for(int j = 0; j < 7; ++j){
      cubes[indexCubes++] = cube_create(0.6f, (Vec3){(float) i * 0.8f, 0.f, j * 0.8f}, &color);
      glVertexAttribPointer(ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, cubes[indexCubes - 1].stride, (void *)0);
      glEnableVertexAttribArray(ATTR_POSITION);
      glVertexAttribPointer(ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, cubes[indexCubes - 1].stride, (void *)(3 * sizeof(float)));
      glEnableVertexAttribArray(ATTR_COLOR);
    }
  }

  glVertexAttribPointer(ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, mesh.stride, (void *)0);
  glEnableVertexAttribArray(ATTR_POSITION);

  glVertexAttribPointer(ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, mesh.stride, (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(ATTR_COLOR);

  glBindVertexArray(0);

  GLuint shader = shader_create(
    "assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl"
  );

  const float PI = 3.1415927f;
  float x = 0.00f, y = 0.0f;
  float angle = 0.0f;
  Vec3 camera = {0.f, 0.f, 0.f};

  int locModel = glGetUniformLocation(shader, "model"); 
  int locView = glGetUniformLocation(shader, "view"); 

  while(!glfwWindowShouldClose(app->window)) {
    Mat4 T = mat4_translate((Vec3) {x, y, 0.0f});
    Mat4 R = mat4_rotate_y(angle * PI / 180);
    Mat4 model = mat4_mul(T, R);
    Mat4 view = mat4_translate((Vec3) {-camera.x, -camera.y, -camera.z});

    glfwPollEvents();
    input_process_key(app->window);

    if(glfwGetKey(app->window, GLFW_KEY_A) == GLFW_PRESS){
      camera.x -= 0.01;
    }

    if(glfwGetKey(app->window, GLFW_KEY_D) == GLFW_PRESS){
      camera.x += 0.01f;
    }

    if(glfwGetKey(app->window, GLFW_KEY_W) == GLFW_PRESS){
      camera.z += 0.01f;  
    }

    if(glfwGetKey(app->window, GLFW_KEY_S) == GLFW_PRESS){
      camera.z -= 0.01f;
    }

    if(glfwGetKey(app->window, GLFW_KEY_SPACE) == GLFW_PRESS){
      camera.y += 0.01f;
    }

    if(glfwGetKey(app->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
      camera.y -= 0.01f;
    }

    if(glfwGetKey(app->window, GLFW_KEY_R) == GLFW_PRESS){
      angle = angle > 360 ? 0 : angle + 1.f;
    }

    if(glfwGetKey(app->window, GLFW_KEY_1) == GLFW_PRESS){
      angle = 0.f;
      camera = (Vec3){0.f, 0.f, 0.f};
    }

    glClearColor(1.f, 1.f, 1.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shader);
    glUniformMatrix4fv(locModel, 1, GL_FALSE, model.data);
    glUniformMatrix4fv(locView, 1, GL_FALSE, view.data);

    glBindVertexArray(mesh.VAO);
    glDrawArrays(GL_TRIANGLES, 0, mesh.numVertices);

    for(int i = 0; i < 49; ++i){
      glBindVertexArray(cubes[i].VAO);
      glDrawArrays(GL_TRIANGLES, 0, cubes[i].numVertices);
    }

    glfwSwapBuffers(app->window);
  }
}

void gameApp_destroy(GameApp *app) {
  window_destroy();
}
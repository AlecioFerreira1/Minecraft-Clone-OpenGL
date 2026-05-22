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

  glfwSetWindowUserPointer(app->window, app);
}

void gameApp_run(GameApp* app) {
  app->scene = scene_create();

  Color color[6] = {
    pallete[COLOR_RED], pallete[COLOR_GREEN], pallete[COLOR_ORANGE],
    pallete[COLOR_LIGHT_GREEN], pallete[COLOR_BLUE], pallete[COLOR_GRAY],  
  };

  Mesh cube = cube_create(0.6, &color);

  for(int i = 0; i < 7; ++i){
    for(int j = 0; j < 7; ++j){
      Entity entity;
      Transform transform = (Transform){
        (Vec3){(float) i * 0.8f, 0.f, j * 0.8f},
        (Vec3){0.f, 0.f, 0.f},
        (Vec3){1.f, 1.f, 1.f},
      };

      entity.mesh = &cube;
      entity.transform = transform;

      scene_add_entity(&app->scene, entity);
    }
  }

  renderer_init(&app->renderer, app->window);

  while(!glfwWindowShouldClose(app->window)) {
    glfwPollEvents();
    input_process_key(app->window, &app->scene.camera);
    camera_update(&app->scene.camera);

    renderer_begin(&app->renderer);
    renderer_set_view(&app->renderer, app->scene.camera.view);

    for(int i = 0; i < app->scene.numEntities; ++i){
      Mat4 model = transform_get_model_matrix(&app->scene.entities[i].transform);
      renderer_draw_mesh(&app->renderer, app->scene.entities[i].mesh, model);
    }
    
    renderer_end(&app->renderer);
  }

  scene_destroy(&app->scene);
}

void gameApp_destroy(GameApp *app) {
  window_destroy();
}
#include "game_app.h"

#include <stdio.h>
#include <math.h>

void gameApp_init(GameApp* app) {
  platform_setup_glfw();

  app->window = window_create("Minecraft Clone OpenGL", 1000, 1000);

  platform_setup_glad();

  int width, height;

  glfwGetFramebufferSize(app->window, &width, &height);
  fix_window_pos(app->window, width, height);
  glfwSetWindowUserPointer(app->window, app);
  
  platform_setup_OpenGL_configs(width, height);
}

void gameApp_run(GameApp* app) {
  app->scene = scene_create();

  Color color[6] = {
    pallete[COLOR_LIGHT_GREEN], pallete[COLOR_BROWN], pallete[COLOR_BROWN],
    pallete[COLOR_BROWN], pallete[COLOR_BROWN], pallete[COLOR_BROWN],
  };

  Mesh cube = cube_create(0.6, &color);

  generate_example_terrain(&app->scene, &cube);
  renderer_init(&app->renderer, app->window);

  while(!glfwWindowShouldClose(app->window)) {
    glfwPollEvents();
    input_process_key(app->window, &app->scene.camera);
    camera_update(&app->scene.camera, window_get_aspect_ratio(app->window));

    renderer_begin(&app->renderer);
    renderer_set_view(&app->renderer, app->scene.camera.view);
    renderer_set_projection(&app->renderer, app->scene.camera.projection);

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

static void fix_window_pos(GLFWwindow* window, int windowWidth, int windowHeight) {
  GLFWmonitor* monitor = glfwGetPrimaryMonitor();
  const GLFWvidmode* mode = glfwGetVideoMode(monitor);

  windowWidth = windowWidth > mode->width ? mode->width : windowWidth;
  windowHeight = windowHeight > mode->height ? mode->height : windowHeight; 

  int x = (mode->width - windowWidth) / 2;
  int y = (mode->height - windowHeight) / 2;

  glfwSetWindowPos(window, x, y);
}

static void generate_example_terrain(Scene* scene, Mesh* cube) {
  for(int i = 0; i < 100; ++i){
    for(int j = 0; j < 100; ++j){
      Entity entity;
      Transform transform = (Transform){
        (Vec3){-20.f + i * 0.6f, 0.f, -20.f + j * 0.6f},
        (Vec3){0.f, 0.f, 0.f},
        (Vec3){1.f, 1.f, 1.f},
      };

      entity.mesh = cube;
      entity.transform = transform;

      scene_add_entity(scene, entity);
    }
  }
}
#include "engine.h"

#include <stb_image.h>
#include <stdio.h>
#include <math.h>

void engine_init(Engine *engine) {
  platform_setup_glfw();

  engine->config = engine_config_get();

  engine->window = window_create(
    "Minecraft Clone OpenGL", engine->config.windowWidth, 
    engine->config.windowHeight, engine->config.vsync
  );

  platform_setup_glad();

  center_window(engine->window, engine->config.windowWidth, engine->config.windowHeight);
  glfwSetWindowUserPointer(engine->window, engine);
  
  platform_setup_OpenGL_configs(engine->config.windowWidth, engine->config.windowHeight);

  engine->lastFrame = glfwGetTime();
  engine->scene = scene_create();
  engine->resourceManager = resource_manager_create();
}

void engine_run(Engine *engine) {
  renderer_init(&engine->renderer, engine->window);
  scene_attach_world_renderer(&engine->scene, engine->resourceManager->textureAtlas);

  while(!glfwWindowShouldClose(engine->window)) {
    glfwPollEvents();
    input_process_key(engine->window, &engine->scene.camera, engine->dt);

    camera_update(&engine->scene.camera, window_get_aspect_ratio(engine->window));
    update_delta_time(engine);
    
    renderer_begin(&engine->renderer);
    renderer_draw_texture_from_atlas(&engine->renderer, engine->resourceManager->textureAtlas);
    renderer_set_view(&engine->renderer, engine->scene.camera.view);
    renderer_set_projection(&engine->renderer, engine->scene.camera.projection);

    scene_update(&engine->scene, &engine->renderer);

    renderer_end(&engine->renderer);
  }
}

void engine_end(Engine *engine) {
  scene_destroy(&engine->scene);
  resource_manager_destroy(engine->resourceManager);
  window_destroy();
}

static void center_window(GLFWwindow* window, int windowWidth, int windowHeight) {
  GLFWmonitor *monitor = glfwGetPrimaryMonitor();
  const GLFWvidmode *mode = glfwGetVideoMode(monitor);

  windowWidth = windowWidth > mode->width ? mode->width : windowWidth;
  windowHeight = windowHeight > mode->height ? mode->height : windowHeight; 

  int x = (mode->width - windowWidth) / 2;
  int y = (mode->height - windowHeight) / 2;

  glfwSetWindowPos(window, x, y);   
}

static void update_delta_time(Engine *engine) {
  engine->dt = glfwGetTime() - engine->lastFrame;
  engine->lastFrame = glfwGetTime();
}
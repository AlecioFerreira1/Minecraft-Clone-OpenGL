#include "engine.h"

#include <stb_image.h>
#include <stdio.h>
#include <math.h>

void engine_init(Engine* engine) {
  platform_setup_glfw();

  engine->window = window_create("Minecraft Clone OpenGL", 1200, 1000);

  platform_setup_glad();

  int width, height;

  glfwGetFramebufferSize(engine->window, &width, &height);
  fix_window_pos(engine->window, width, height);
  glfwSetWindowUserPointer(engine->window, engine);
  
  platform_setup_OpenGL_configs(width, height);

  engine->scene = scene_create();
  engine->resourceManager = resource_manager_create();
  engine->lastFrame = glfwGetTime();
}

void engine_run(Engine* engine) {
  generate_example_terrain(engine);
  renderer_init(&engine->renderer, engine->window);

  while(!glfwWindowShouldClose(engine->window)) {
    glfwPollEvents();
    input_process_key(engine->window, &engine->scene.camera, engine->dt);
    camera_update(&engine->scene.camera, window_get_aspect_ratio(engine->window));
    update_delta_time(engine);

    renderer_begin(&engine->renderer);
    renderer_draw_texture_from_atlas(&engine->renderer, engine->resourceManager->textureAtlas);
    renderer_set_view(&engine->renderer, engine->scene.camera.view);
    renderer_set_projection(&engine->renderer, engine->scene.camera.projection);

    for(int i = 0; i < engine->scene.numEntities; ++i){
      Mat4 model = transform_get_model_matrix(&engine->scene.entities[i].transform);
      renderer_draw_mesh(&engine->renderer, engine->scene.entities[i].mesh, model);
    }

    renderer_end(&engine->renderer);
  }
}

void engine_destroy(Engine *engine) {
  scene_destroy(&engine->scene);
  resource_manager_destroy(engine->resourceManager);
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

static void update_delta_time(Engine* engine) {
  engine->dt = glfwGetTime() - engine->lastFrame;
  engine->lastFrame = glfwGetTime();
}

static void generate_example_terrain(Engine* engine) {
  const BlockId blockType = BLOCK_GRASS;
  const AtlasTile top = REGISTERED_BLOCKS[blockType].top;
  const AtlasTile bottom = REGISTERED_BLOCKS[blockType].bottom;
  const AtlasTile left = REGISTERED_BLOCKS[blockType].left;
  const AtlasTile right = REGISTERED_BLOCKS[blockType].right;
  const AtlasTile front = REGISTERED_BLOCKS[blockType].front;
  const AtlasTile back = REGISTERED_BLOCKS[blockType].back;

  const CubeUVSet uvSet = {
    uv_rect_convert(top, engine->resourceManager->textureAtlas),
    uv_rect_convert(bottom, engine->resourceManager->textureAtlas),
    uv_rect_convert(left, engine->resourceManager->textureAtlas),
    uv_rect_convert(right, engine->resourceManager->textureAtlas),
    uv_rect_convert(front, engine->resourceManager->textureAtlas),
    uv_rect_convert(back, engine->resourceManager->textureAtlas),
  };

  Mesh* cube = cube_create(0.6f, uvSet);

  resource_manager_add_mesh(engine->resourceManager, "grass", cube);

  for(int i = 0; i < 100; ++i){
    for(int j = 0; j < 100; ++j){
      for(int k = 0; k < 1; ++k){
        Entity entity;
        Transform transform = (Transform){
          (Vec3){-20.f + i * 0.6f, -k * 0.6f, -20.f + j * 0.6f},
          (Vec3){0.f, 0.f, 0.f},
          (Vec3){1.f, 1.f, 1.f},
        };

        entity.mesh = cube;   
        entity.transform = transform;

        scene_add_entity(&engine->scene, entity);
      }
    }
  }
}
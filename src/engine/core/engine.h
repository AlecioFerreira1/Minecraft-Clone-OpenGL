#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../platform/platform.h"
#include "../input/input.h"
#include "../window/window.h"
#include "../graphics/shader/shader.h"
#include "../graphics/mesh/mesh.h"
#include "../config/engine_config.h"
#include "../debug/debug_info.h"

#include "../graphics/mesh/primitives/cube.h"
#include "../math/mat4.h"
#include "../scene/scene.h"
#include "../renderer/renderer.h"
#include "../resource_manager/resource_manager.h"

typedef struct {
  GLFWwindow *window;
  Scene scene;
  Renderer renderer;
  ResourceManager *resourceManager;
  EngineConfig config;
  DebugInfo debug;

  float dt;
  float lastFrame;
} Engine;

void engine_init(Engine *engine);
void engine_run(Engine *engine);
void engine_end(Engine *engine);
static void center_window(GLFWwindow *window, int width, int height);
static void update_delta_time(Engine *engine);
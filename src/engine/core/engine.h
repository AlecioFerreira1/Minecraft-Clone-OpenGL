#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../platform/platform.h"
#include "../input/input.h"
#include "../window/window.h"

#include "../graphics/shader/shader.h"
#include "../graphics/mesh/mesh.h"
#include "../graphics/mesh/primitives/cube.h"

#include "../math/mat4.h"
#include "../scene/scene.h"
#include "../renderer/renderer.h"
#include "../resource_manager/resource_manager.h"
#include "../world/registry/block_registry.h"

typedef struct {
  GLFWwindow* window;
  Scene scene;
  Renderer renderer;
  ResourceManager* resourceManager;
  float dt;
  float lastFrame;
} Engine;

void engine_init(Engine* app);
void engine_run(Engine* app);
void engine_destroy(Engine* app);
static void fix_window_pos(GLFWwindow* window, int width, int height);
static void generate_example_terrain(Engine* engine);
static void update_delta_time(Engine* engine);
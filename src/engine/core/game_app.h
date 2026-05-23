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

typedef struct {
  GLFWwindow* window;
  Scene scene;
  Renderer renderer;
} GameApp;

void gameApp_init(GameApp* app);
void gameApp_run(GameApp* app);
void gameApp_destroy(GameApp* app);
static void fix_window_pos(GLFWwindow* window, int width, int height);
static void generate_example_terrain(Scene* scene, Mesh* cube);
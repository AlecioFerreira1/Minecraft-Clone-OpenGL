#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../platform/platform.h"
#include "../input/input.h"
#include "../window/window.h"
#include "../graphics/shader.h"
#include "../../utils/utils.h"

typedef struct {
    GLFWwindow* window;
} GameApp;

void gameApp_init(GameApp* app);
void gameApp_run(GameApp* app);
void gameApp_destroy(GameApp* app);
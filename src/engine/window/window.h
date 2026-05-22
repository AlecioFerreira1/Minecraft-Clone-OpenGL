#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#include "../input/input.h"

GLFWwindow* window_create(const char* title, int width, int height);
void window_destroy();
static void framebuffer_size_callback(GLFWwindow* window, int width, int height); 
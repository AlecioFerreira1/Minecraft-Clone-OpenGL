#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

void platform_setup_glfw();
void platform_setup_glad();
void platform_setup_OpenGL_configs(int width, int height);
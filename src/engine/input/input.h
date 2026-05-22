#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>

#include "../scene/camera/camera.h"

void input_process_key(GLFWwindow* window, Camera* camera);
static void handle_camera(GLFWwindow* window, Camera* camera);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
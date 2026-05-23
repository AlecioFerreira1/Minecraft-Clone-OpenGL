#include "input.h"
#include "../core/game_app.h"

static float lastX = 0.f;
static float lastY = 0.f;

void input_process_key(GLFWwindow* window, Camera* camera) {
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  handle_camera(window, camera);
}

static void handle_camera(GLFWwindow* window, Camera* camera) {
  if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
    camera->position = vec3_sub(
      camera->position, 
      vec3_scale(camera->right, camera->speed)
    );
  }

  if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
    camera->position = vec3_sum(
      camera->position, 
      vec3_scale(camera->right, camera->speed)
    );
  }

  if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
    camera->position = vec3_sum(
      camera->position, 
      vec3_scale(camera->forward, camera->speed)
    );  
  }

  if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
    camera->position = vec3_sub(
      camera->position, 
      vec3_scale(camera->forward, camera->speed)
    );
  }

  if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
     camera->position = vec3_sum(
      camera->position, 
      vec3_scale(WORLD_UP, camera->speed)
    );
  }

  if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
    camera->position = vec3_sub(
      camera->position, 
      vec3_scale(WORLD_UP, camera->speed)
    );
  }

  if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS){
    camera->yaw = 0.f;
    camera->pitch = 0.f;
    camera->position = (Vec3){0.f, 0.f, -1.f};
  }
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
  float xOffset = xPos - lastX;
  float yOffset = lastY - yPos;

  lastX = (float) xPos;
  lastY = (float) yPos;

  GameApp* app = glfwGetWindowUserPointer(window);

  camera_process_mouse(&app->scene.camera, xOffset, yOffset);
}
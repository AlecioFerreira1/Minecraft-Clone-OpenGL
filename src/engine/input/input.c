#include "input.h"
#include "../core/engine.h"

static float lastX = 0.f;
static float lastY = 0.f;

void input_process_key(GLFWwindow* window, Camera* camera, float dt) {
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  handle_camera(window, camera, dt);
}

static void handle_camera(GLFWwindow* window, Camera* camera, float dt) {
  const Vec3 moveForward = vec3_normalize((Vec3){
    camera->forward.x, 0.f, camera->forward.z
  }); 

  const Vec3 moveRight = vec3_normalize((Vec3){
    camera->right.x, 0.f, camera->right.z
  }); 

  if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
    camera->position = vec3_sub(
      camera->position, 
      vec3_scale(moveRight, camera->speed * dt)
    );
  }

  if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
    camera->position = vec3_sum(
      camera->position, 
      vec3_scale(moveRight, camera->speed * dt)
    );
  }

  if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
    camera->position = vec3_sum(
      camera->position, 
      vec3_scale(moveForward, camera->speed * dt)
    );  
  }

  if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
    camera->position = vec3_sub(
      camera->position, 
      vec3_scale(moveForward, camera->speed * dt)
    );
  }

  if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
     camera->position = vec3_sum(
      camera->position, 
      vec3_scale(WORLD_UP, camera->speed * dt)
    );
  }

  if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
    camera->position = vec3_sub(
      camera->position, 
      vec3_scale(WORLD_UP, camera->speed * dt)
    );
  }

  if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS){
    camera->yaw = 0.f;
    camera->pitch = 0.f;
    camera->position = (Vec3) {0.f, 0.f, 0.f};
  }
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
  float xOffset = xPos - lastX;
  float yOffset = lastY - yPos;

  lastX = (float) xPos;
  lastY = (float) yPos;

  Engine* engine = glfwGetWindowUserPointer(window);

  camera_process_mouse(&engine->scene.camera, xOffset, yOffset);
}
#include "camera.h" 

Camera camera_create() {
  Camera camera;

  camera.position = (Vec3) {0.f, 0.f, 0.f};
  camera.yaw = 0.f;
  camera.pitch = 0.f;
  camera.forward = (Vec3) {0.f, 0.f, -1.f};
  camera.right = (Vec3) {1.f, 0.f, 0.f};
  camera.up = (Vec3) {0.f, 1.f, 0.f};
  camera.view = mat4_identity();
  camera.sensitivity = 0.1;
  camera.speed = 0.01;

  return camera;
}

void camera_update(Camera* camera) {
  camera->forward = (Vec3) {
    cosf(camera->yaw) * cosf(camera->pitch), 
    sinf(camera->pitch), 
    sinf(camera->yaw) * cosf(camera->pitch)
  };

  camera->right = vec3_normalize(vec3_cross(camera->forward, WORD_UP));
  camera->up = vec3_normalize(vec3_cross(camera->right, camera->forward));

  camera->view = mat4_lookAt(
    camera->position, camera->forward, camera->right, camera->up
  ); 
}

void camera_process_mouse(Camera* camera, float xOffset, float yOffset) {
  const float CONVERT_TO_RADIANS = 0.01745329251f;

  camera->yaw += (xOffset * camera->sensitivity) * CONVERT_TO_RADIANS;
  camera->pitch += (yOffset * camera->sensitivity) * CONVERT_TO_RADIANS;

  if(camera->pitch > (89.f) * CONVERT_TO_RADIANS) camera->pitch = 89.f * CONVERT_TO_RADIANS;
  if(camera->pitch < (-89.f) * CONVERT_TO_RADIANS) camera->pitch = -89.f * CONVERT_TO_RADIANS;

  camera_update(camera);
}
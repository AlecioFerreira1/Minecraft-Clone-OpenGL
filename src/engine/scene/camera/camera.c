#include "camera.h" 

static const float CONVERT_TO_RADIANS = 0.01745329251f;

Camera camera_create() {
  Camera camera;

  camera.position = (Vec3) {0.f, 1.f, 0.f};
  camera.yaw = 0.f;
  camera.pitch = 0.f;
  camera.forward = (Vec3) {0.f, 0.f, -1.f};
  camera.right = (Vec3) {1.f, 0.f, 0.f};
  camera.up = (Vec3) {0.f, 1.f, 0.f};
  camera.sensitivity = 0.1;
  camera.speed = 5;
  camera.fov = 90 * CONVERT_TO_RADIANS;
  camera.near = 0.1;
  camera.far = 1000;

  return camera;
}

void camera_update(Camera* camera, float aspectRatio) {
  camera->aspect = aspectRatio;

  camera->forward = (Vec3) {
    cosf(camera->yaw) * cosf(camera->pitch), 
    sinf(camera->pitch), 
    sinf(camera->yaw) * cosf(camera->pitch)
  };

  camera->right = vec3_normalize(vec3_cross(camera->forward, WORLD_UP));
  camera->up = vec3_normalize(vec3_cross(camera->right, camera->forward));

  camera->view = mat4_lookAt(
    camera->position, camera->forward, camera->right, camera->up
  ); 

  camera->projection = projection_perspective(
    camera->aspect, camera->fov, camera->near, camera->far
  );
}

void camera_process_mouse(Camera* camera, float xOffset, float yOffset) {
  camera->yaw += (xOffset * camera->sensitivity) * CONVERT_TO_RADIANS;
  camera->pitch += (yOffset * camera->sensitivity) * CONVERT_TO_RADIANS;

  if(camera->pitch > (89.f) * CONVERT_TO_RADIANS) camera->pitch = 89.f * CONVERT_TO_RADIANS;
  if(camera->pitch < (-89.f) * CONVERT_TO_RADIANS) camera->pitch = -89.f * CONVERT_TO_RADIANS;

  camera_update(camera, camera->aspect);
}
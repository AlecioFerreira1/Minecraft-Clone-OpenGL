#include "camera.h" 

Camera camera_create() {
  Camera camera;

  camera.position = (Vec3) {7.5f, 100.f, 7.5f};
  camera.yaw = 0.f;
  camera.pitch = 0.f;
  camera.forward = (Vec3) {0.f, 0.f, -1.f};
  camera.right = (Vec3) {1.f, 0.f, 0.f};
  camera.up = (Vec3) {0.f, 1.f, 0.f};
  camera.near = 0.1;
  camera.far = 1000;
  camera.config = camera_config_get();

  return camera;
}

void camera_update(Camera *camera, float aspectRatio) {
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
    camera->aspect, camera->config.fov, camera->near, camera->far
  );
}

void camera_process_mouse(Camera *camera, float xOffset, float yOffset) {
  camera->yaw += (xOffset * camera->config.sensitivity) * CONVERT_TO_RADIANS;
  camera->pitch += (yOffset * camera->config.sensitivity) * CONVERT_TO_RADIANS;

  if(camera->pitch > (89.f) * CONVERT_TO_RADIANS) camera->pitch = 89.f * CONVERT_TO_RADIANS;
  if(camera->pitch < (-89.f) * CONVERT_TO_RADIANS) camera->pitch = -89.f * CONVERT_TO_RADIANS;

  camera_update(camera, camera->aspect);
}
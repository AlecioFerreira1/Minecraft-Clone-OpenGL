#pragma once

#include "../../math/vec3.h"
#include "../../math/mat4.h"
#include "../../math/projection.h"

static const Vec3 WORLD_UP = {0, 1, 0};

typedef struct {
  float sensitivity;
  float speed;
  Vec3 position;
  float yaw, pitch;
  Vec3 forward; 
  Vec3 up;
  Vec3 right;
  Mat4 view;
  float near, far;
  float aspect, fov;
  Mat4 projection;
} Camera;   

Camera camera_create();
void camera_update(Camera* camera, float aspectRatio);
void camera_process_mouse(Camera* camera, float xOffset, float yOffset);
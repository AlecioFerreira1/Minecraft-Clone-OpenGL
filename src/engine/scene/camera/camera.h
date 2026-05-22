#pragma once

#include "../../math/vec3.h"
#include "../../math/mat4.h"

static const Vec3 WORD_UP = {0, 1, 0};

typedef struct {
  Vec3 position;
  float yaw;
  float pitch;
  Vec3 forward; 
  Vec3 up;
  Vec3 right;
  Mat4 view;
  float sensitivity;
  float speed;
} Camera;   

Camera camera_create();
void camera_update(Camera* camera);
void camera_process_mouse(Camera* camera, float xOffset, float yOffset);
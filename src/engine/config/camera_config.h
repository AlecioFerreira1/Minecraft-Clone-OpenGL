#pragma once

#include "../math/convert_to_radians.h"

typedef struct {
  float sensitivity;
  float speed;
  float fov;
} CameraConfig;

CameraConfig camera_config_get();
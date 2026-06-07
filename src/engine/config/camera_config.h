#pragma once

#define CONVERT_TO_RADIANS 0.01745329251f

typedef struct {
  float sensitivity;
  float speed;
  float fov;
} CameraConfig;

CameraConfig camera_config_get();
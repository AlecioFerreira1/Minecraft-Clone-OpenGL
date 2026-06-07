#include "camera_config.h"

CameraConfig camera_config_get() {
  CameraConfig config;
  
  config.fov = 90.f * CONVERT_TO_RADIANS;
  config.sensitivity = 0.1f;
  config.speed = 15.f;

  return config;
}
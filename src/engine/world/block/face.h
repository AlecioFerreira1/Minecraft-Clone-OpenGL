#pragma once

#include "../../math/vec3.h"

typedef enum {
  FACE_TOP, 
  FACE_BOTTOM, 
  FACE_LEFT, 
  FACE_RIGHT, 
  FACE_FRONT, 
  FACE_BACK
} Face;

Vec3 face_to_normal(Face face);
Face normal_to_face(Vec3 normal);
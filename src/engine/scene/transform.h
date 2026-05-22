#pragma once

#include "../math/vec3.h"
#include "../math/mat4.h"

typedef struct {
  Vec3 position;
  Vec3 rotation;
  Vec3 scale;
} Transform;

Mat4 transform_get_model_matrix(Transform* transform);
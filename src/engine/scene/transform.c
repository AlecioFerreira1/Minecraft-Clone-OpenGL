#include "transform.h"

Mat4 transform_get_model_matrix(Transform* transform) {
  Mat4 T = mat4_translate(transform->position);
  Mat4 Rx = mat4_rotate_x(transform->rotation.x);
  Mat4 Ry = mat4_rotate_y(transform->rotation.y);
  Mat4 Rz = mat4_rotate_z(transform->rotation.z);
  Mat4 R = mat4_mul(mat4_mul(Rz, Ry), Rx);
  Mat4 S = mat4_scale(transform->scale);
  Mat4 model = mat4_mul(mat4_mul(T, R), S);

  return model;
}
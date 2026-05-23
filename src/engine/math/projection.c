#include "projection.h"

Mat4 projection_perspective(float aspect, float fov, float near, float far) {
  Mat4 perspective = mat4_identity();

  float f = 1/tanf(fov / 2);

  perspective.data[0] = f / aspect;
  perspective.data[5] = f;
  perspective.data[10] = (far + near) / (near - far);
  perspective.data[11] = -1;
  perspective.data[14] = (2 * far * near) / (near - far);

  return perspective;
}
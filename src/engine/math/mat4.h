#include <math.h>

#include "vec3.h"

typedef struct {
  float data[16];
} Mat4;

Mat4 mat4_identity();
Mat4 mat4_translate(Vec3 t);
Mat4 mat4_scale(Vec3 s);
Mat4 mat4_rotate_z(float angle);
Mat4 mat4_rotate_x(float angle);
Mat4 mat4_rotate_y(float angle);
Mat4 mat4_mul(Mat4 a, Mat4 b);
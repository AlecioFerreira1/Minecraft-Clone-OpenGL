#include "vec3.h"

Vec3 vec3_sum(Vec3 v0, Vec3 v1) {
  return (Vec3) {v0.x + v1.x, v0.y + v1.y, v0.z + v1.z};
}

Vec3 vec3_sub(Vec3 v0, Vec3 v1) {
  return (Vec3) {v0.x - v1.x, v0.y - v1.y, v0.z - v1.z};
}

Vec3 vec3_scale(Vec3 v, float s) {
  return (Vec3) {s * v.x, s * v.y, s * v.z};
}

float vec3_lenght(Vec3 v) {
  return (float) (sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
}

Vec3 vec3_normalize(Vec3 v) {
  float vLenght = vec3_lenght(v);

  return (Vec3) {v.x / vLenght, v.y / vLenght, v.z / vLenght};
}

float vec3_dot(Vec3 v0, Vec3 v1) {
  return (v0.x * v1.x) + (v0.y * v1.y) + (v0.z * v1.z);
}

Vec3 vec3_cross(Vec3 v0, Vec3 v1) {
  return (Vec3) {
    (v0.y * v1.z) - (v0.z * v1.y), 
    (v0.z * v1.x) - (v0.x * v1.z), 
    (v0.x * v1.y) - (v0.y * v1.x)
  };
}

Vec3 vec3_rotate(Vec3 v, Mat3 rotate) {
  return (Vec3) {
    .x = v.x * rotate.data[0] + v.y * rotate.data[3] + v.z * rotate.data[6],
    .y = v.x * rotate.data[1] + v.y * rotate.data[4] + v.z * rotate.data[7],
    .z = v.x * rotate.data[2] + v.y * rotate.data[5] + v.z * rotate.data[8]
  };
}
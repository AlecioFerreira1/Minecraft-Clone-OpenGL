#include "mat4.h"

Mat4 mat4_identity() {
  Mat4 mat4;

  for(int i = 0; i < 16; ++i){
    if(i % 5 == 0) mat4.data[i] = 1.0f;
    else mat4.data[i] = 0.0f;
  }
  
  return mat4;
}

Mat4 mat4_translate(Vec3 t) {
  Mat4 mat4Translate = mat4_identity();

  mat4Translate.data[12] = t.x;
  mat4Translate.data[13] = t.y;
  mat4Translate.data[14] = t.z;

  return mat4Translate;
}

Mat4 mat4_scale(Vec3 s) {
  Mat4 mat4Scale = mat4_identity();

  mat4Scale.data[0] = s.x;
  mat4Scale.data[5] = s.y;
  mat4Scale.data[10] = s.z;

  return mat4Scale;
}

Mat4 mat4_rotate_z(float angle) {
  Mat4 mat4RotateZ = mat4_identity();
  
  mat4RotateZ.data[0] = (float) cos(angle);
  mat4RotateZ.data[1] = (float) sin(angle);
  mat4RotateZ.data[4] = (float) -sin(angle);
  mat4RotateZ.data[5] = (float) cos(angle);
  
  return mat4RotateZ;
}

Mat4 mat4_rotate_x(float angle) {
  Mat4 mat4RotateX = mat4_identity();
  
  mat4RotateX.data[5] = (float) cos(angle);
  mat4RotateX.data[6] = (float) sin(angle);
  mat4RotateX.data[9] = (float) -sin(angle);
  mat4RotateX.data[10] = (float) cos(angle);
  
  return mat4RotateX;
}

Mat4 mat4_rotate_y(float angle) {
  Mat4 mat4RotateY = mat4_identity();
  
  mat4RotateY.data[0] = (float) cos(angle);
  mat4RotateY.data[2] = (float) -sin(angle);
  mat4RotateY.data[8] = (float) sin(angle);
  mat4RotateY.data[10] = (float) cos(angle);
  
  return mat4RotateY;
}

Mat4 mat4_mul(Mat4 a, Mat4 b) {
  Mat4 res;

  for(int i = 0; i < 4; ++i) {
    for(int j = 0; j < 4; ++j) {
      float value = 0.00f;

      for(int k = 0; k < 4; ++k) {
        value += (a.data[i + (k * 4)] * b.data[k + (j * 4)]);
      }

      res.data[i + (j * 4)] = value;
    }
  }

  return res;
}
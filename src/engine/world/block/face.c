#include "face.h"

Vec3 face_to_normal(Face face) {
  if(face == FACE_RIGHT) return (Vec3) {1, 0, 0};
  else if(face == FACE_LEFT) return (Vec3) {-1, 0, 0};
  else if(face == FACE_TOP) return (Vec3) {0, 1, 0};
  else if(face == FACE_BOTTOM) return (Vec3) {0, -1, 0};
  else if(face == FACE_FRONT) return (Vec3) {0, 0, -1};
  else return (Vec3) {0, 0, 1};
}

Face normal_to_face(Vec3 normal) {
  if(normal.x == 1) return FACE_RIGHT;
  else if(normal.x == -1) return FACE_LEFT;
  else if(normal.y == 1) return FACE_TOP;
  else if(normal.y == -1) return FACE_BOTTOM;
  else if(normal.z == 1) return FACE_BACK;
  else return FACE_FRONT;
}
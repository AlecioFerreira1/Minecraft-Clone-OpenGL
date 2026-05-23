#pragma once

typedef enum {
  COLOR_RED, COLOR_GREEN, COLOR_BLUE, COLOR_ORANGE, COLOR_LIGHT_GREEN,
  COLOR_GRAY, COLOR_BROWN, COLOR_COUNT
} ColorType;

typedef struct {
  float r;
  float g;
  float b;
} Color;

extern Color pallete[COLOR_COUNT];
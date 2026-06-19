#pragma once

#include <GLFW/glfw3.h>
#include <stdio.h>

typedef struct {
  int fps;
  int frameTime;
} DebugInfo;

void debug_info_display_logs(DebugInfo *debugInfo);
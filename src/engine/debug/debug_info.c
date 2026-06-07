#include "debug_info.h"

void debug_info_display_logs(DebugInfo* debugInfo) {
  printf("\nFPS: %d\tFRAMETIME: %s ms\n", debugInfo->fps, debugInfo->frameTime);
}

// void debug_update_info(DebugInfo* debugInfo, )
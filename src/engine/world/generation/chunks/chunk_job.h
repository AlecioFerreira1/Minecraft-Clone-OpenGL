#pragma once

#include <stdint.h>

#include "chunk_coords.h"

typedef struct {
  int priority;
  ChunkCoords coords;
} ChunkJob;

int8_t chunk_job_compare(const void *chunkJobA, const void *coordsB);
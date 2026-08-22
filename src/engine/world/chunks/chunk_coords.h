#pragma once

#include <stdbool.h>

typedef struct {
  int x;  
  int y;
  int z;
} ChunkCoords;

bool chunk_coords_equals(ChunkCoords chunkA, ChunkCoords chunkB);
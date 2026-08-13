#pragma once

#include "chunk.h"

typedef struct {
  int8_t start_i;
  int8_t start_j;
  int8_t end_i;
  int8_t end_j;
} MaskRect;

void greedy_meshing(
  Vector *vertices, uint16_t (*mask)[CHUNK_SIZE][CHUNK_SIZE], 
  Vec3 chunkPosOnWorld, const float plane, Vec3 normal, 
  const float BLOCK_SIZE, TextureAtlas *textures
);

static Vec3 mask_coords_to_world_coords(
  Vec3 chunkWorldPos, Vec2 maskCoords, Vec3 normal, const float planeVal
);

static void greedy_meshing_expand_right(
  uint16_t (*mask)[CHUNK_SIZE][CHUNK_SIZE], MaskRect *currentRect, int8_t current_i, int8_t current_j
);

static void greedy_meshing_expand_below(
  uint16_t (*mask)[CHUNK_SIZE][CHUNK_SIZE], MaskRect *currentRect, int8_t current_i, int8_t current_j
);
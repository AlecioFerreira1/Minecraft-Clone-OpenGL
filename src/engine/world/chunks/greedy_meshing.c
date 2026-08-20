#include "greedy_meshing.h"
#include "../../graphics/geometry/quad.h"
#include "../block/block_registry.h"

void  greedy_meshing(
  Vector *vertices, uint16_t (*mask)[CHUNK_SIZE][CHUNK_SIZE], 
  Vec3 chunkPosOnWorld, const float plane, Vec3 normal, TextureAtlas *textures
) {
  int8_t row = 0, col = 0;

  ChunkCoords chunkCoords = world_coords_to_chunk_coords(chunkPosOnWorld);

  while(row < CHUNK_SIZE) {
    for( ; col < CHUNK_SIZE && (*mask)[row][col] == BLOCK_AIR; ++col);

    MaskRect currentRect = {row, col, row, col};

    if(col < CHUNK_SIZE && (*mask)[row][col] != BLOCK_AIR) {
      currentRect.blockType = (*mask)[row][col];
      greedy_meshing_expand_right(mask, &currentRect, row, col);
      greedy_meshing_expand_below(mask, &currentRect, row + 1, col);

      Vec3 chunkSliceBottomLeft = mask_coords_to_world_coords(chunkPosOnWorld, currentRect, normal, plane);
      UVrect uvRect = block_registry_get_uv_rect(currentRect.blockType, normal_to_face(normal), textures);

      Vector chunkSlice2D = quad_gen_vertices(
        chunkSliceBottomLeft, 
        (float)(currentRect.end_col - currentRect.start_col + 1), 
        (float)(currentRect.end_row - currentRect.start_row + 1), 
        normal, uvRect
      );

      vector_append_many(vertices, &chunkSlice2D);
      vector_destroy(&chunkSlice2D);

      if(currentRect.end_col < (CHUNK_SIZE - 1)) {
        row = currentRect.start_row;
        col = currentRect.end_col + 1;
      }

      else {
        col = 0;
        row = currentRect.end_row + 1;
      }

      continue;
    }

    ++row;
  }
}

static Vec3 mask_coords_to_world_coords(Vec3 chunkPosOnWorld, MaskRect currentRect, Vec3 normal, const float plane) {
  Vec3 localChunkCoords;

  if(normal.x != 0.f) {
    localChunkCoords.x = plane;
    localChunkCoords.y = currentRect.start_row;
    localChunkCoords.z = currentRect.start_col;
  }

  else if(normal.y != 0.f) {
    localChunkCoords.y = plane;
    localChunkCoords.x = currentRect.start_col;
    localChunkCoords.z = currentRect.start_row;
  }

  else {
    localChunkCoords.z = plane;
    localChunkCoords.x = currentRect.start_col;
    localChunkCoords.y = currentRect.start_row;
  }

  return vec3_sum(chunkPosOnWorld, localChunkCoords);
}

static void greedy_meshing_expand_right(
  uint16_t (*mask)[CHUNK_SIZE][CHUNK_SIZE], MaskRect *currentRect, int8_t row, int8_t col
) {
  for(int8_t j = col; (j < CHUNK_SIZE) && (*mask)[row][j] == currentRect->blockType; ++j) {
    (*mask)[row][j] = BLOCK_AIR;
    currentRect->end_col = j;
  }
}

static void greedy_meshing_expand_below(
  uint16_t (*mask)[CHUNK_SIZE][CHUNK_SIZE], MaskRect *currentRect, int8_t row, int8_t col
) {
  if(row >= CHUNK_SIZE) return;

  int8_t i = row;

  while(i < CHUNK_SIZE) {
    bool rowCompleted = true;

    for(int8_t j = currentRect->start_col; (j <= currentRect->end_col) && rowCompleted; ++j) {
      rowCompleted = rowCompleted && ((*mask)[i][j] == currentRect->blockType);
    }

    if(rowCompleted) {
      for(int8_t j = currentRect->start_col; j <= currentRect->end_col; ++j) {
        (*mask)[i][j] = BLOCK_AIR;
        currentRect->end_row = i;
      }
    } 

    else break;

    ++i;
  }
}
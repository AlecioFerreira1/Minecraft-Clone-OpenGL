#include "greedy_meshing.h"
#include "../../graphics/geometry/quad.h"
#include "../block/block_registry.h"

void greedy_meshing(
  Vector *vertices, uint16_t (*mask)[CHUNK_SIZE][CHUNK_SIZE], 
  Vec3 chunkPosOnWorld, const float plane, Vec3 normal, 
  const float BLOCK_SIZE, TextureAtlas *textures
) {
  int8_t current_i = 0, current_j = 0;

  for( ; current_i < CHUNK_SIZE; ++current_i) {
    for( ; current_j < CHUNK_SIZE && (*mask)[current_i][current_j] == BLOCK_AIR; ++current_j);

    MaskRect currentRect = {current_i, current_j, current_i, current_j};

    if((*mask)[current_i][current_j] != BLOCK_AIR) {
      Block blockType = (*mask)[current_i][current_j];

      greedy_meshing_expand_right(mask, &currentRect, current_i, current_j);
      greedy_meshing_expand_below(mask, &currentRect, current_i + 1, current_j);

      Vec3 chunkSliceStartPos = mask_coords_to_world_coords(
        chunkPosOnWorld, (Vec2) {currentRect.start_i, currentRect.start_j}, normal, plane
      );

      UVrect uvRect = block_registry_get_uv_rect(blockType, normal_to_face(normal), textures);

      Vector chunkSlice2D = quad_gen_vertices(
        chunkSliceStartPos, (float) (currentRect.end_j - currentRect.start_j + 1), 
        (float) (currentRect.end_i - currentRect.start_i + 1), BLOCK_SIZE, normal, uvRect
      );

      vector_append_many(vertices, &chunkSlice2D);
      vector_destroy(&chunkSlice2D);
        
      for(int8_t i = currentRect.start_i; i <= currentRect.end_i; ++i) {
        for(int8_t j = currentRect.start_j; j <= currentRect.end_j; ++j) {
          (*mask)[i][j] = BLOCK_AIR;
        }
      }

      if(currentRect.end_j < (CHUNK_SIZE - 1)) {
        current_i = currentRect.start_i + 1;
        current_j = currentRect.end_j + 1;
      }

      else {
        current_j = 0;
        current_i = currentRect.end_i + 1;
      }
    }
  }
}

static Vec3 mask_coords_to_world_coords(Vec3 chunkPosOnWorld, Vec2 maskCoords, Vec3 normal, const float plane) {
  Vec3 localChunkCoords;

  if(normal.x == 1 || normal.x == -1) {
    localChunkCoords.x = plane;
    localChunkCoords.y = maskCoords.x;
    localChunkCoords.z = maskCoords.y;
  }

  else if(normal.y == 1 || normal.y == -1) {
    localChunkCoords.y = plane;
    localChunkCoords.x = maskCoords.x;
    localChunkCoords.z = maskCoords.y;
  }

  else {
    localChunkCoords.z = plane;
    localChunkCoords.x = maskCoords.x;
    localChunkCoords.y = maskCoords.y;
  }

  return vec3_sum(chunkPosOnWorld, localChunkCoords);
}

static void greedy_meshing_expand_right(
  uint16_t (*mask)[CHUNK_SIZE][CHUNK_SIZE], MaskRect *currentRect, int8_t current_i, int8_t current_j
) {
  int8_t j = current_j;
  Block blockType = (*mask)[current_i][current_j];

  for( ; (j < CHUNK_SIZE) && (*mask)[current_i][j] == blockType; ++j) {
    (*mask)[current_i][j] = BLOCK_AIR;
    currentRect->end_j = j;
  }
}

static void greedy_meshing_expand_below(
  uint16_t (*mask)[CHUNK_SIZE][CHUNK_SIZE], MaskRect *currentRect, int8_t current_i, int8_t current_j
) {
  Block blockType = (*mask)[current_i][current_j];
  int8_t i = current_i;

  while(i < CHUNK_SIZE) {
    bool rowCompleted = true;

    for(int8_t j = currentRect->start_j; (j <= currentRect->end_j) && rowCompleted; ++j) {
      rowCompleted = rowCompleted && ((*mask)[i][j] == blockType);
    }

    if(rowCompleted) {
      for(int8_t j = currentRect->start_j; j <= currentRect->end_j; ++j) {
        (*mask)[i][j] = BLOCK_AIR;
        currentRect->end_i = i;
      }
    } 

    else break;

    ++i;
  }
}
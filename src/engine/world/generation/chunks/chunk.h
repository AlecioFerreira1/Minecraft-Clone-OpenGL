#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "../../../config/world_config.h"
#include "../../../graphics/mesh/mesh.h"
#include "../../../math/vec3.h"
#include "../world_generator.h"
#include "chunk_coords.h"

typedef enum {
  CHUNK_STATE_ACTIVE,
  CHUNK_STATE_PENDING_UNLOAD,
  CHUNK_STATE_DESTROYED
} ChunkState;

typedef struct {
  uint16_t blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
  bool dirty;
  Mesh *mesh;
  ChunkCoords coords;
  ChunkState state;
} Chunk;

Chunk *chunk_create(ChunkCoords chunkCoords, WorldGenerator *generator);
void chunk_destroy(Chunk *chunk);
ChunkCoords world_coords_to_chunk_coords(Vec3 worldCoords);
Vec3 chunk_coords_to_world_coords(ChunkCoords chunkCoords);
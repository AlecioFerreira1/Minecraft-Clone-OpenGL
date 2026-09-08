#pragma once

#include "chunk.h"
#include "chunk_job.h"
#include "../../graphics/geometry/quad.h"
#include "../../../data_structures/priority_queue.h"
#include "../../../data_structures/vector.h"
#include "../../graphics/geometry/vertex.h"
#include "../../graphics/geometry/vertices_group.h"

typedef struct {
  HashMap *chunks;
  TextureAtlas *textures;
  PriorityQueue rebuildQueue;
  int8_t rebuildBudget;
  ChunkCoords lastPlayerChunk;
  bool hasPlayerChunk;
} ChunkBuilder;

ChunkBuilder chunk_builder_create(HashMap *chunks, TextureAtlas *textures);
static void chunk_builder_build_chunk_mesh(ChunkBuilder* chunkBuilder, Chunk *chunk);
void chunk_builder_update_chunks(ChunkBuilder *chunkBuilder, Vec3 playerPos);

static void fill_mask_by_axis_in_coords_ijk(
  HashMap *chunks, const Chunk *chunk, uint16_t (*mask)[CHUNK_SIZE][CHUNK_SIZE], 
  Vec3 normal, uint8_t i, uint8_t j, uint8_t k
);
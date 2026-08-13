#pragma once

#include "chunk.h"
#include "chunk_job.h"
#include "../../graphics/geometry/quad.h"
#include "../../../data_structures/priority_queue.h"
#include "../../../data_structures/vector.h"
#include "../../graphics/geometry/vertex.h"

typedef struct {
  HashMap *chunks;
  TextureAtlas *textures;
  PriorityQueue rebuildQueue;
  int8_t rebuildBudget;
} ChunkBuilder;

ChunkBuilder chunk_builder_create(HashMap *chunks, TextureAtlas *textures);
static void chunk_builder_build_chunk_mesh(ChunkBuilder* chunkBuilder, Chunk *chunk);
static void add_chunk_slice_to_vertices(Vector *vertices, Vector *chunkSliceVertices);
void chunk_builder_update_chunks(ChunkBuilder *chunkBuilder, Vec3 playerPos);
static Vector build_2D_chunk_slice(ChunkBuilder *chunkBuilder, const Chunk *chunk, Vec3 normal);
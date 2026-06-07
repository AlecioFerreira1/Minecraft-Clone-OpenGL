#pragma once

#include "chunk.h"
#include "../../../graphics/geometry/quad.h"

typedef struct {
  HashMap* chunks;
  TextureAtlas* textures;
} ChunkBuilder;

ChunkBuilder chunk_builder_create(HashMap* chunks, TextureAtlas* textures);
static void chunk_builder_build_chunk_mesh(ChunkBuilder* chunkBuilder, Chunk* chunk);
static void add_face_vertices_to_chunk(float** chunkVertices, size_t* nValues, float* quad);
void chunk_builder_update_chunks(ChunkBuilder* chunkBuilder);
#pragma once

#include "../config/world_config.h"
#include "chunks/chunk.h"
#include "generation/world_generator.h"
#include "../../data_structures/hash_map.h"
#include "../../data_structures/priority_queue.h"
#include "chunks/chunk_job.h"

typedef struct {
  WorldConfig config;
  HashMap chunks;
  WorldGenerator worldGenerator;
  WorldType type;
  int8_t destroyBudget;
  PriorityQueue destroyQueue;
} World;

World world_create(WorldType worldType);
void world_destroy(World *world);
void world_update(World *world, Vec3 playerPos);
uint16_t world_block_at(HashMap *chunks, Vec3 worldCoords);
static bool chunk_already_loaded(HashMap *chunks, char *chunkName);
static void world_discard_chunks_out_of_range(World *world, ChunkCoords playerChunk, int renderDistanceStart, int renderDistanceEnd);
static void world_mark_dirty(World *world, ChunkCoords chunkCoords); 
Chunk *world_get_chunk(HashMap *chunks, ChunkCoords chunkCoords);
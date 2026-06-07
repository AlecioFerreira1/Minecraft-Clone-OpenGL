#pragma once

#include "../config/world_config.h"
#include "generation/chunks/chunk.h"
#include "generation/world_generator.h"
#include "../../data_structures/hash_map.h"

typedef struct {
  WorldConfig config;
  HashMap chunks;
  WorldGenerator worldGenerator;
  WorldType type;
} World;

World world_create(WorldType worldType);
void world_destroy(World* world);
void world_update(World* world, Vec3 playerPos);
uint16_t world_block_at(HashMap* chunks, Vec3 worldCoords);
static bool chunk_already_loaded(HashMap* chunks, char* chunkName);
static void world_discard_chunks_out_of_range(World* world, Vec3 playerPos, float renderDistanceStart, float renderDistanceEnd);
static void world_mark_dirty(World* world, ChunkCoords chunkCoords); 
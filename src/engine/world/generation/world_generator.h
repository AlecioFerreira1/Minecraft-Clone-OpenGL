#pragma once 

#include <stdint.h>

#include "../../config/world_config.h"
#include "../block/block.h"
#include "../../../data_structures/hash_map.h"
#include "../../math/vec3.h"
#include "type/world_type.h"
#include "../chunks/chunk_coords.h"
#include "type/superflat.h"
#include "type/default.h"

typedef struct Chunk Chunk;

typedef struct {
  int32_t seed;
  WorldType worldType;
  
  struct {
    Superflat superflat;
    Default default_;
  } config;
} WorldGenerator;

WorldGenerator world_generator_create(int32_t seed, WorldType worldType);
void world_generator_generate_chunk(WorldGenerator *generator, Chunk *chunk); 
void world_generator_remove_resources(WorldGenerator *generator);
static void generate_super_flat(WorldGenerator *generator, Chunk *chunk);
static void generate_default(WorldGenerator *generator, Chunk *chunk);
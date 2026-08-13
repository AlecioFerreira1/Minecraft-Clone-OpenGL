#pragma once 

#include <stdint.h>

#include "../../config/world_config.h"
#include "../block/block.h"
#include "../../../data_structures/hash_map.h"
#include "../../math/vec3.h"
#include "type/world_type.h"
#include "../chunks/chunk_coords.h"

typedef struct {
  uint32_t seed;
  WorldType worldType;
} WorldGenerator;

WorldGenerator world_generator_create(uint32_t seed, WorldType worldType);

uint16_t world_generator_generate_block(
  WorldGenerator *generator, ChunkCoords chunkCoords, uint8_t localChunkX, uint8_t localChunkY, uint8_t localChunkZ
);
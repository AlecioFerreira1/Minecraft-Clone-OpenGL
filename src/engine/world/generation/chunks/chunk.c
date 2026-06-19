#include "chunk.h"

Chunk *chunk_create(ChunkCoords chunkCoords, WorldGenerator *generator) {
  Chunk *chunk = malloc(sizeof(Chunk));

  chunk->mesh = NULL;
  chunk->dirty = true;
  chunk->coords = chunkCoords;

  for(uint8_t x = 0; x < CHUNK_SIZE; ++x){
    for(uint8_t y = 0; y < CHUNK_SIZE; ++y){
      for(uint8_t z = 0; z < CHUNK_SIZE; ++z){
        chunk->blocks[x][y][z] = world_generator_generate_block(generator, chunk->coords, x, y, z); 
      }
    } 
  }

  return chunk;
}

void chunk_destroy(Chunk *chunk) {
  mesh_destroy(chunk->mesh);
  free(chunk); 
}

ChunkCoords world_coords_to_chunk_coords(Vec3 worldCoords) {
  return (ChunkCoords) {
    (int) floor(worldCoords.x / CHUNK_SIZE),
    (int) floor(worldCoords.y / CHUNK_SIZE),
    (int) floor(worldCoords.z / CHUNK_SIZE),
  };
}

Vec3 chunk_coords_to_world_coords(ChunkCoords chunkCoords) {
  return (Vec3) {
    (float) chunkCoords.x * CHUNK_SIZE,
    (float) chunkCoords.y * CHUNK_SIZE,
    (float) chunkCoords.z * CHUNK_SIZE,
  };
}
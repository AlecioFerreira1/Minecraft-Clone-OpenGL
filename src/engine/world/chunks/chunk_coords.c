#include "chunk_coords.h"

bool chunk_coords_equals(ChunkCoords chunkA, ChunkCoords chunkB) {
  return (chunkA.x == chunkB.x && chunkA.y == chunkB.y && chunkA.z == chunkB.z);
}
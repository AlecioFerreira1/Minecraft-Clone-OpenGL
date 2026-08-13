#include "chunk_job.h"

int8_t chunk_job_compare(const void *chunkJobA, const void *chunkJobB) {
  const ChunkJob *chunkJob_A = (const ChunkJob *) chunkJobA;
  const ChunkJob *chunkJob_B = (const ChunkJob *) chunkJobB;

  if(chunkJob_A->priority > chunkJob_B->priority) return 1;
  else if(chunkJob_A->priority < chunkJob_B->priority) return -1;
  else return 0;
}
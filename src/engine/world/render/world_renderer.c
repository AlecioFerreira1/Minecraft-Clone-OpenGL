#include "world_renderer.h"

WorldRenderer world_renderer_create(HashMap *chunks, TextureAtlas *textures) {
  WorldRenderer worldRenderer;

  worldRenderer.chunkBuilder = chunk_builder_create(chunks, textures);

  return worldRenderer;
}

void world_renderer_render(WorldRenderer *worldRenderer, Renderer *renderer, Vec3 playerPos) {
  chunk_builder_update_chunks(&worldRenderer->chunkBuilder, playerPos);

  HashMap *chunks = worldRenderer->chunkBuilder.chunks;

  for(size_t i = 0; i < chunks->capacity; ++i) {
    if(chunks->entries[i].key != NULL) {
      Chunk *chunk = (Chunk *) chunks->entries[i].value;

      if(chunk->mesh != NULL) {
        renderer_draw_mesh(renderer, chunk->mesh, mat4_identity());
      }
    }
  }
}
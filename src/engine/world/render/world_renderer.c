#include "world_renderer.h"

WorldRenderer world_renderer_create(HashMap *chunks, TextureAtlas *textures) {
  WorldRenderer worldRenderer;

  worldRenderer.chunkBuilder = chunk_builder_create(chunks, textures);

  return worldRenderer;
}

void world_renderer_render(WorldRenderer *worldRenderer, Renderer *renderer, Vec3 playerPos) {
  chunk_builder_update_chunks(&worldRenderer->chunkBuilder, playerPos);
  process_chunks_by_render_mode(worldRenderer, renderer, RENDER_MODE_OPAQUE);
  process_chunks_by_render_mode(worldRenderer, renderer, RENDER_MODE_CUTOUT);
  process_chunks_by_render_mode(worldRenderer, renderer, RENDER_MODE_BLEND);
}

static void process_chunks_by_render_mode(WorldRenderer *worldRenderer, Renderer *renderer, RenderMode mode) {
  HashMap *chunks = worldRenderer->chunkBuilder.chunks;
  uint8_t submeshIndex = 0;

  if(mode == RENDER_MODE_OPAQUE) submeshIndex = 0;
  else if(mode == RENDER_MODE_CUTOUT) submeshIndex = 1;
  else submeshIndex = 2;

  for(size_t i = 0; i < chunks->capacity; ++i) {
    if(chunks->entries[i].key != NULL) {
      Chunk *chunk = (Chunk *) chunks->entries[i].value;

      if(chunk != NULL && chunk->mesh != NULL) {
        renderer_draw_submesh(renderer, chunk->mesh, mat4_identity(), submeshIndex);
      }
    }
  }
}
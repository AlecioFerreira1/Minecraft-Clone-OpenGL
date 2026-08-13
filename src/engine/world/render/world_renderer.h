#pragma once

#include "../chunks/chunk_builder.h"
#include "../../graphics/texture/texture.h"
#include "../../renderer/renderer.h"

typedef struct {
  ChunkBuilder chunkBuilder;
} WorldRenderer;

WorldRenderer world_renderer_create(HashMap *chunks, TextureAtlas *textures);
void world_renderer_render(WorldRenderer *worldRenderer, Renderer *renderer, Vec3 playerPos);
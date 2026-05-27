#pragma once

#include <glad/glad.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
  GLuint id;
  uint32_t width;
  uint32_t height;
} Texture;

typedef struct {
  GLuint id;
  uint32_t width;
  uint32_t height;
  uint32_t tileSize;
} TextureAtlas;

Texture* texture_load(const char* path);
TextureAtlas* texture_load_atlas(const char* path, uint32_t tileSize);
void texture_destroy(Texture* texture);
void texture_atlas_destroy(TextureAtlas* textureAtlas);
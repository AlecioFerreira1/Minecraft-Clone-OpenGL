#include "texture.h"

#include <stb_image.h>

Texture* texture_load(const char* path) {
  int width, height, channels;

  unsigned char* data = stbi_load(path, &width, &height, &channels, 0); 

  if(data == NULL) {
    fprintf(stderr, "Failed to load image '%s': %s\n", path, stbi_failure_reason());
    return NULL;
  }

  GLuint textureId;

  glGenTextures(1, &textureId);
  glBindTexture(GL_TEXTURE_2D, textureId);

  GLenum format = channels == 3 ? GL_RGB : GL_RGBA;

  glTexImage2D(
    GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data
  );

  Texture* texture = malloc(sizeof(Texture));

  texture->id = textureId;
  texture->width = width;
  texture->height = height;

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  stbi_image_free(data);

  return texture;
}

TextureAtlas* texture_load_atlas(const char* path, uint32_t tileSize) {
  Texture* texture = texture_load(path);
  
  if(texture == NULL) return NULL;

  TextureAtlas* textureAtlas = malloc(sizeof(TextureAtlas));

  textureAtlas->id = texture->id;
  textureAtlas->width = texture->width;
  textureAtlas->height = texture->height;
  textureAtlas->tileSize = tileSize;

  free(texture);

  return textureAtlas;
}

void texture_destroy(Texture* texture) {
  if(texture != NULL) {
    glDeleteTextures(1, &texture->id);
    free(texture);
  }
}

void texture_atlas_destroy(TextureAtlas* textureAtlas) {
  if(textureAtlas != NULL) {
    glDeleteTextures(1, &textureAtlas->id);
    free(textureAtlas);
  }
}
#pragma once

#include "../../data_structures/hash_map.h"
#include "../graphics/texture/texture.h"
#include "../graphics/mesh/mesh.h"

typedef struct {
  HashMap textures;
  TextureAtlas *textureAtlas;
} ResourceManager;

ResourceManager *resource_manager_create();
void resource_manager_destroy(ResourceManager *resourceManager);
void resource_manager_add_texture(ResourceManager *resourceManager, char *key, Texture *texture);
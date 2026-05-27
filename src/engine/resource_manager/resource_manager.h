#pragma once

#include "../../data_structures/hash_map.h"
#include "../graphics/texture/texture.h"
#include "../graphics/mesh/mesh.h"
// #include "../graphics/material/material.h"

typedef struct {
  HashMap meshs;
  HashMap textures;
  HashMap materials;
  TextureAtlas* textureAtlas;
} ResourceManager;

ResourceManager* resource_manager_create();
void resource_manager_destroy(ResourceManager* resourceManager);
void resource_manager_add_texture(ResourceManager* resourceManager, char* key, Texture* texture);
void resource_manager_add_mesh(ResourceManager* resourceManager, char* key, Mesh* mesh);
// void resource_manager_add_material(ResourceManager* resourceManager, const char* key, Material* material);
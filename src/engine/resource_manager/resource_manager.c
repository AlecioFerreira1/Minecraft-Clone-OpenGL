#include "resource_manager.h"

ResourceManager* resource_manager_create() {
  ResourceManager* resourceManager = malloc(sizeof(ResourceManager));

  hash_map_create(&resourceManager->meshs, 5);
  hash_map_create(&resourceManager->textures, 5);
  hash_map_create(&resourceManager->materials, 5);

  resourceManager->textureAtlas = texture_load_atlas("assets/textures/textures.png", 16);

  return resourceManager;
}

void resource_manager_destroy(ResourceManager* resourceManager) {
  for(int i = 0; i < resourceManager->textures.capacity; ++i){
    if(resourceManager->textures.elements[i].state == HASH_MAP_ENTRY_STATE_OCCUPIED){
      texture_destroy((Texture *) resourceManager->textures.elements[i].value);
    }
  }

  for(int i = 0; i < resourceManager->meshs.capacity; ++i){
    if(resourceManager->meshs.elements[i].state == HASH_MAP_ENTRY_STATE_OCCUPIED){
      mesh_destroy((Mesh *) resourceManager->meshs.elements[i].value);
    }
  }

  for(int i = 0; i < resourceManager->materials.capacity; ++i){
    if(resourceManager->materials.elements[i].state == HASH_MAP_ENTRY_STATE_OCCUPIED){
      free(resourceManager->materials.elements[i].value);
    }
  }

  hash_map_destroy(&resourceManager->meshs);
  hash_map_destroy(&resourceManager->textures);
  hash_map_destroy(&resourceManager->materials);

  texture_atlas_destroy(resourceManager->textureAtlas);

  free(resourceManager);
}

void resource_manager_add_texture(ResourceManager* resourceManager, char* key, Texture* texture) {
  if(hash_map_search(&resourceManager->textures, key) == -1){
    hash_map_insert(&resourceManager->textures, key, texture);
    return;
  }

  texture_destroy(texture);
}

void resource_manager_add_mesh(ResourceManager* resourceManager, char* key, Mesh* mesh) {
  if(hash_map_search(&resourceManager->meshs, key) == -1){
    hash_map_insert(&resourceManager->meshs, key, mesh);
    return;
  }

  mesh_destroy(mesh);
}

// void resource_manager_add_material(ResourceManager* resourceManager, const char* key, Material* material) {
//   if(hash_map_search(&resourceManager->materials, key) == -1){
//     hash_map_insert(&resourceManager->materials, key, material);
//     return;
//   }

//   free(material);
// }
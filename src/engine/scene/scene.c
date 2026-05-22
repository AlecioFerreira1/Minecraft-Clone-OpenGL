#include "scene.h"

Scene scene_create() {
  return (Scene) {camera_create(), NULL, 0};
}

void scene_destroy(Scene* scene) {
  scene->numEntities = 0;
  free(scene->entities);
}

void scene_add_entity(Scene* scene, Entity entity) {
  Entity* newEntity = realloc(scene->entities, (scene->numEntities + 1) * sizeof(Entity));

  if(newEntity != NULL) {
    scene->entities = newEntity;
    scene->entities[scene->numEntities++] = entity; 
    return;
  }

  printf("Erro ao adicionar uma entidade gráfica!\nId da entidade: %d", (scene->entities));
}
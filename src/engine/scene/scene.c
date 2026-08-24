#include "scene.h"

Scene scene_create() {
  Scene scene;

  scene.camera = camera_create();
  scene.world = world_create(WORLD_TYPE_DEFAULT);
  scene.numEntities = 0;
  scene.entities = NULL;

  return scene;
}

void scene_attach_world_renderer(Scene *scene, TextureAtlas *textures) {
  scene->worldRenderer = world_renderer_create(&scene->world.chunks, textures);
}

void scene_destroy(Scene *scene) {
  scene->numEntities = 0;
  free(scene->entities);
  world_destroy(&scene->world);
}

void scene_add_entity(Scene *scene, Entity entity) {
  Entity *newEntity = realloc(scene->entities, (scene->numEntities + 1) * sizeof(Entity));

  if(newEntity != NULL) {
    scene->entities = newEntity;
    scene->entities[scene->numEntities++] = entity; 
    return;
  }

  printf("Erro ao adicionar uma entidade!\nId da entidade: %d", (scene->entities));
}

void scene_update(Scene *scene, Renderer *renderer) {
  world_update(&scene->world, scene->camera.position);
  world_renderer_render(&scene->worldRenderer, renderer, scene->camera.position);

  for(int i = 0; i < scene->numEntities; ++i){
    Mat4 model = transform_get_model_matrix(&scene->entities[i].transform);
    renderer_draw_mesh(renderer, scene->entities[i].mesh, model);
  }
}
#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "camera/camera.h"
#include "entity.h"
#include "../world/world.h"
#include "../renderer/renderer.h"
#include "../world/render/world_renderer.h"

typedef struct {
  Camera camera;
  Entity *entities;
  int numEntities;
  World world;
  WorldRenderer worldRenderer;
} Scene;

Scene scene_create();
void scene_destroy(Scene *scene);
void scene_add_entity(Scene *scene, Entity entity);
void scene_update(Scene *scene, Renderer *renderer);
void scene_attach_world_renderer(Scene *scene, TextureAtlas *textures);
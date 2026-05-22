#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "camera/camera.h"
#include "entity.h"

typedef struct {
  Camera camera;
  Entity* entities;
  int numEntities;
} Scene;

Scene scene_create();
void scene_destroy(Scene* scene);
void scene_add_entity(Scene* scene, Entity entity);
#pragma once

#include "vegetation_type.h"
#include "../../math/vec3.h"

typedef struct {
  Vec3 position;
  VegetationType type;
} Vegetation;
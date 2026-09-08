#pragma once

#include <stdbool.h>

#include "../../graphics/material/material.h"
#include "vegetation_type.h"

typedef struct {
  Material material;
  bool solid;
} VegetationDefinition;

extern const VegetationDefinition REGISTERED_VEGETATIONS[VEGETATION_COUNT];
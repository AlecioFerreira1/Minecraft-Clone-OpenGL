#pragma once

#include <stdbool.h>

typedef enum {
  VEGETATION_SHORT_GRASS,
  VEGETATION_TALL_GRASS,
  VEGETATION_DEAD_BUSH,
  VEGETATION_DANDELION,
  VEGETATION_POPPY,
  VEGETATION_BLUE_ORCHID,
  VEGETATION_ALLIUM,
  VEGETATION_AZURE_BLUET,
  VEGETATION_RED_TULIP,
  VEGETATION_ORANGE_TULIP,
  VEGETATION_WHITE_TULIP,
  VEGETATION_PINK_TULIP,
  VEGETATION_OXEYE_DAISY,
  VEGETATION_OAK_TREE,
  VEGETATION_COUNT
} VegetationType;

bool vegetation_type_simple(VegetationType type);
bool vegetation_type_double(VegetationType type);
bool vegetation_type_structure(VegetationType type);
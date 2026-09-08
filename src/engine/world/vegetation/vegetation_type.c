#include "vegetation_type.h"

bool vegetation_type_simple(VegetationType type) {
  return !vegetation_type_double(type) && !vegetation_type_structure(type);
}

bool vegetation_type_double(VegetationType type) {
  return type == VEGETATION_TALL_GRASS;
}

bool vegetation_type_structure(VegetationType type) {
  return type == VEGETATION_OAK_TREE;
}
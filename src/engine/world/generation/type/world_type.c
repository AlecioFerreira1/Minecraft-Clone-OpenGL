#include "world_type.h"
#include "superflat.h"

WorldTypeConfig world_type_get_config(WorldType worldType) { 
  if(worldType == WORLD_TYPE_SUPERFLAT) {
    return superflat_get_config();
  }

  return superflat_get_config();
}
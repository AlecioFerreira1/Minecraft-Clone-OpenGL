#include "vegetation_builder.h"
#include "vegetation_definition.h"
#include "geometry/simple_vegetation.h"
#include "geometry/double_vegetation.h"

#include <stdio.h>

void vegetation_builder_create_vertices(VerticesGroup *verticesGroup, const Vector *vegetation, TextureAtlas *textures) {
  for(size_t i = 0; i < vector_size(vegetation); ++i) {
    const Vegetation *currVegetation = vector_get_item(vegetation, i);

    if(vegetation_type_none(currVegetation->type)) continue;

    Material material = REGISTERED_VEGETATIONS[currVegetation->type].material;

    if(vegetation_type_simple(currVegetation->type)) {
      Vector simpleVegetationVertices = simple_vegetation_gen_vertices(*currVegetation, textures, material);

      vertices_group_add(verticesGroup, &simpleVegetationVertices, material.renderMode);
    }

    else if(vegetation_type_double(currVegetation->type)) {
      Vector doubleVegetationVertices = double_vegetation_gen_vertices(*currVegetation, textures);

      vertices_group_add(verticesGroup, &doubleVegetationVertices, material.renderMode);
    }

    else;
  }
}
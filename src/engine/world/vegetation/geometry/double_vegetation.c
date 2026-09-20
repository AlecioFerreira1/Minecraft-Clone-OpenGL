#include "double_vegetation.h"

Vector double_vegetation_gen_vertices(const Vegetation vegetation, TextureAtlas *textures) {
  Vector vertices = vector_create(VECTOR_MIN_CAPACITY, sizeof(Vertex));
  
  Material material = REGISTERED_VEGETATIONS[vegetation.type].material;
  Material upper_material = REGISTERED_VEGETATIONS[vegetation.type].upper_material;

  Vegetation topVegetation;

  topVegetation.type = vegetation.type;
  topVegetation.position = vec3_sum(vegetation.position, (Vec3) {0.f, 1.f, 0.f});

  Vector baseVegetationVertices = simple_vegetation_gen_vertices(vegetation, textures, material);
  Vector topVegetationVertices = simple_vegetation_gen_vertices(topVegetation, textures, upper_material);

  vector_append_many(&vertices, &baseVegetationVertices);
  vector_append_many(&vertices, &topVegetationVertices);

  vector_destroy(&baseVegetationVertices);
  vector_destroy(&topVegetationVertices);

  return vertices;
}
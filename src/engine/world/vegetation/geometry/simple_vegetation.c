#include "simple_vegetation.h"
#include "../../../math/convert_to_radians.h"

Vector simple_vegetation_gen_vertices(const Vegetation vegetation, TextureAtlas *textures, Material material) {
  Vector vertices = vector_create(12, sizeof(Vertex));
  UVrect quadUv = uv_rect_convert(material.tile, textures);
  Vec3 visualPos = vec3_sum(vegetation.position, (Vec3) {0.f, 0.f, 0.5f});

  Vector quadTranslated = quad_gen_vertices(
    visualPos, (Vec2) {1.f, 1.f}, material.color, (Vec3) {0.0, 0.f, 1.f}, 
    quadUv, false, 0.f, (Vec3) {0.f, 1.f, 0.f}
  );

  Vector quadRotated90 = quad_gen_vertices(
    visualPos, (Vec2) {1.f, 1.f}, material.color, (Vec3) {0.0, 0.f, 1.f}, 
    quadUv, false, 90.f * CONVERT_TO_RADIANS, (Vec3) {0.f, 1.f, 0.f}
  );

  if(material.doubleSized) {
    Vector quadTranslatedReverseWinding = quad_gen_vertices(
      visualPos, (Vec2) {1.f, 1.f}, material.color, (Vec3) {0.0, 0.f, 1.f}, 
      quadUv, true, 0.f, (Vec3) {0.f, 1.f, 0.f}
    );

    Vector quadRotated90ReverseWinding = quad_gen_vertices(
      visualPos, (Vec2) {1.f, 1.f}, material.color, (Vec3) {0.0, 0.f, 1.f}, 
      quadUv, true, 90.f * CONVERT_TO_RADIANS, (Vec3) {0.f, 1.f, 0.f}
    );

    vector_append_many(&vertices, &quadTranslatedReverseWinding);
    vector_append_many(&vertices, &quadRotated90ReverseWinding);

    vector_destroy(&quadTranslatedReverseWinding);
    vector_destroy(&quadRotated90ReverseWinding);
  }

  vector_append_many(&vertices, &quadTranslated);
  vector_append_many(&vertices, &quadRotated90);

  vector_destroy(&quadTranslated);
  vector_destroy(&quadRotated90);

  return vertices;
}
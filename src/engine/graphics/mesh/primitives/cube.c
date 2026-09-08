#include "cube.h"
#include "../../geometry/vertices_group.h"

Mesh *cube_create(Vec3 center, float size, CubeMaterial cubeMaterial) {
  VerticesGroup verticesGroup = vertices_group_create();
  Vec3 min = vec3_sub(center, (Vec3) {size / 2, size / 2, size / 2});
  Vec3 max = vec3_sum(center, (Vec3) {size / 2, size / 2, size / 2});

  Vector faceTop = quad_gen_vertices(
    (Vec3) {min.x, max.y, min.z}, size, size, cubeMaterial.top.color, (Vec3){0, 1, 0}, 
    uv_rect_convert(cubeMaterial.top.tile, cubeMaterial.textures), false 
  );
  
  Vector faceBottom = quad_gen_vertices(
    (Vec3) {min.x, min.y, min.z}, size, size, cubeMaterial.bottom.color, (Vec3){0, -1, 0}, 
    uv_rect_convert(cubeMaterial.bottom.tile, cubeMaterial.textures), false
  );
  
  Vector faceLeft = quad_gen_vertices(
    (Vec3) {min.x, min.y, min.z}, size, size, cubeMaterial.left.color, (Vec3){-1, 0, 0}, 
    uv_rect_convert(cubeMaterial.left.tile, cubeMaterial.textures), false
  );
  
  Vector faceRight = quad_gen_vertices(
    (Vec3) {max.x, min.y, min.z}, size, size, cubeMaterial.right.color, (Vec3){1, 0, 0}, 
    uv_rect_convert(cubeMaterial.right.tile, cubeMaterial.textures), false
  );
  
  Vector faceFront = quad_gen_vertices(
    (Vec3) {min.x, min.y, min.z}, size, size, cubeMaterial.front.color, (Vec3){0, 0, -1}, 
    uv_rect_convert(cubeMaterial.front.tile, cubeMaterial.textures), false
  );

  Vector faceBack = quad_gen_vertices(
    (Vec3) {min.x, min.y, max.z}, size, size, cubeMaterial.back.color, (Vec3){0, 0, 1}, 
    uv_rect_convert(cubeMaterial.back.tile, cubeMaterial.textures), false
  );

  vertices_group_add(&verticesGroup, &faceTop, cubeMaterial.top.renderMode);
  vertices_group_add(&verticesGroup, &faceBottom, cubeMaterial.bottom.renderMode);
  vertices_group_add(&verticesGroup, &faceLeft, cubeMaterial.left.renderMode);
  vertices_group_add(&verticesGroup, &faceRight, cubeMaterial.right.renderMode);
  vertices_group_add(&verticesGroup, &faceFront, cubeMaterial.front.renderMode);
  vertices_group_add(&verticesGroup, &faceBack, cubeMaterial.back.renderMode);

  vector_destroy(&faceTop);
  vector_destroy(&faceBottom);
  vector_destroy(&faceLeft);
  vector_destroy(&faceRight);
  vector_destroy(&faceFront);
  vector_destroy(&faceBack);

  Vector vertices = vector_create(VECTOR_MIN_CAPACITY, sizeof(Vertex));
  Vector subMeshes = vector_create(3, sizeof(SubMesh));

  SubMesh opaqueSubmesh = {0, vector_size(&verticesGroup.opaqueVertices), RENDER_MODE_OPAQUE};
  SubMesh cutoutSubmesh = {vector_size(&verticesGroup.opaqueVertices), vector_size(&verticesGroup.cutoutVertices), RENDER_MODE_CUTOUT};
  SubMesh blendSubmesh = {
    vector_size(&verticesGroup.opaqueVertices) + vector_size(&verticesGroup.cutoutVertices), 
    vector_size(&verticesGroup.blendVertices), RENDER_MODE_BLEND
  };

  vector_append_many(&vertices, &verticesGroup.opaqueVertices);
  vector_append_many(&vertices, &verticesGroup.cutoutVertices);
  vector_append_many(&vertices, &verticesGroup.blendVertices);

  vector_push_back(&subMeshes, &opaqueSubmesh);
  vector_push_back(&subMeshes, &cutoutSubmesh);
  vector_push_back(&subMeshes, &blendSubmesh);

  Mesh *mesh = mesh_create((Vertex *) vertices.data, vertices.size, &subMeshes, GL_STATIC_DRAW);

  vector_destroy(&vertices);
  vector_destroy(&subMeshes);
  vertices_group_destroy(&verticesGroup);

  return mesh;
}
#include "vertices_group.h"
#include "vertex.h"

VerticesGroup vertices_group_create() {
  VerticesGroup verticesGroup;

  verticesGroup.opaqueVertices = vector_create(VECTOR_MIN_CAPACITY, sizeof(Vertex));
  verticesGroup.cutoutVertices = vector_create(1, sizeof(Vertex));
  verticesGroup.blendVertices = vector_create(1, sizeof(Vertex));

  return verticesGroup;
}

void vertices_group_destroy(VerticesGroup *verticesGroup) {
  vector_destroy(&verticesGroup->opaqueVertices);
  vector_destroy(&verticesGroup->cutoutVertices);
  vector_destroy(&verticesGroup->blendVertices);
}

void vertices_group_add(VerticesGroup *verticesGroup, const Vector *vertices, RenderMode renderMode) {
  switch(renderMode) {
    case RENDER_MODE_CUTOUT:
      vertices_group_add_cutout(verticesGroup, vertices);
      break;

    case RENDER_MODE_BLEND:
      vertices_group_add_blend(verticesGroup, vertices);
      break;

    default:
      vertices_group_add_opaque(verticesGroup, vertices);
      break;
  }
}

static void vertices_group_add_opaque(VerticesGroup *verticesGroup, const Vector *opaqueVertices) {
  vector_append_many(&verticesGroup->opaqueVertices, opaqueVertices);
}

static void vertices_group_add_cutout(VerticesGroup *verticesGroup, const Vector *cutoutVertices) {
  vector_append_many(&verticesGroup->cutoutVertices, cutoutVertices);
}

static void vertices_group_add_blend(VerticesGroup *verticesGroup, const Vector *blendVertices) {
  vector_append_many(&verticesGroup->blendVertices, blendVertices);
}
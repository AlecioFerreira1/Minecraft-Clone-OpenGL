#pragma once

#include "../../../data_structures/vector.h"
#include "render_mode.h"

typedef struct {
  Vector opaqueVertices;
  Vector cutoutVertices;
  Vector blendVertices;
} VerticesGroup;

VerticesGroup vertices_group_create();
void vertices_group_destroy(VerticesGroup *verticesGroup);
void vertices_group_add(VerticesGroup *verticesGroup, const Vector *vertices, RenderMode renderMode);
static void vertices_group_add_opaque(VerticesGroup *verticesGroup, const Vector *opaqueVertices);
static void vertices_group_add_cutout(VerticesGroup *verticesGroup, const Vector *cutoutVertices);
static void vertices_group_add_blend(VerticesGroup *verticesGroup, const Vector *blendVertices);
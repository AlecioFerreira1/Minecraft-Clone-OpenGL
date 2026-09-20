#pragma once

#include "../../graphics/geometry/vertices_group.h"
#include "vegetation.h"
#include "../../graphics/texture/texture.h"

void vegetation_builder_create_vertices(VerticesGroup *verticesGroup, const Vector *vegetation, TextureAtlas *textures);
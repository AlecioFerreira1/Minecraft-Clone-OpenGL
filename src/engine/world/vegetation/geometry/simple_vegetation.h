#pragma once

#include "../vegetation.h"
#include "../../../../data_structures/vector.h"
#include "../../../graphics/geometry/quad.h"
#include "../vegetation_definition.h"

Vector simple_vegetation_gen_vertices(const Vegetation vegetation, TextureAtlas *textures, Material material);
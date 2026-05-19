#pragma once

#include "../../graphics/mesh.h"
#include "../../graphics/color/color.h"
#include "../vertices.h"

Mesh cube_create(float size, Vec3 pos, Color (*color)[6]);
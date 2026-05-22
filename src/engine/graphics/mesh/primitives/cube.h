#pragma once

#include "../mesh.h"
#include "../../color/color.h"
#include "../../geometry/quad.h"

Mesh cube_create(float size, Color (*color)[6]);
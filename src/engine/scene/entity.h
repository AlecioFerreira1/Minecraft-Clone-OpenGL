#pragma once

#include "transform.h"
#include "../graphics/mesh/mesh.h"

typedef struct {
  Transform transform;
  Mesh* mesh;
} Entity;
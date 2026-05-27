#pragma once

#include "transform.h"
#include "../graphics/mesh/mesh.h"
// #include "../graphics/material/material.h"

typedef struct {
  Transform transform;
  Mesh* mesh;
  // Material* material;
} Entity;
#pragma once

#include "world_type.h"
#include "../../../config/world_config.h"
#include "../../block/block.h"
#include "../../vegetation/vegetation.h"
#include "../../../math/noise.h"
#include "../../../math/vec3.h"

typedef struct {
  int minHeight;
  int maxHeight;
  float frequency;
  float amplitude;
  float baseTerrainHeight;
  float maxTerrainHeight;
  float waterMaxHeight;
  float vegetationMinHeight;
  float vegetationMaxHeight;
} Default;

Default default_get_config();
Block default_get_block_on_y_level(Default config, float worldY);
static float terrain_height(Default config, Vec3 worldCoords, float seed);
float default_terrain_height_generation(Default config, Vec3 worldCoords, float seed);
static float small_scale_octave(Vec3 worldCoords, float seed);
static float medium_scale_octave(Vec3 worldCoords, float seed);
static float mountain_noise(Vec3 worldCoords, float seed);
static float plain_noise(Vec3 worldCoords, float seed);
static float lake_depression_octave(Vec3 worldCoords, float seed);
static float lake_depression_noise(Vec3 worldCoords, float seed);
Vegetation default_vegetation_generation(Default config, Vec3 worldCoords, float seed);
static float vegetation_noise(Vec3 worldCoords, float seed);
static float vegetation_type_noise(Vec3 worldCoords, float seed);
static VegetationType vegetation_get_type_by_noise_value(Vec3 worldCoords, float seed);
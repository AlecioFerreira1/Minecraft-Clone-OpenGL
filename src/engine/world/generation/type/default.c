#include "default.h"

#include <stdio.h>
Default default_get_config() {
  Default config;

  config.maxHeight = world_config_get().worldMaxHeight;
  config.minHeight = world_config_get().worldMinHeight;
  config.baseTerrainHeight = 66.f;
  config.maxTerrainHeight = 128.f;
  config.amplitude = (config.maxTerrainHeight - config.baseTerrainHeight) - 40.f;
  config.frequency = 0.005f;
  config.waterMaxHeight = 66.f;
  config.vegetationMinHeight = config.baseTerrainHeight;
  config.vegetationMaxHeight = config.maxTerrainHeight - 40.f;

  return config;
}

Block default_get_block_on_y_level(Default config, float worldY) {
  if(worldY > config.maxTerrainHeight || worldY < config.minHeight) return BLOCK_AIR;
  else if(worldY > config.maxTerrainHeight - 40.f) return BLOCK_STONE; 
  else if(worldY >= config.baseTerrainHeight) return BLOCK_GRASS;
  else if(worldY > 60.f) return BLOCK_DIRT;
  else if(worldY > 2.f) return BLOCK_STONE;
  else return BLOCK_BEDROCK;
}

static float terrain_height(Default config, Vec3 worldCoords, float seed) {
  float noise = noise2D(worldCoords.x * config.frequency, worldCoords.z * config.frequency, seed);

  return (config.baseTerrainHeight + noise * config.amplitude);
}

float default_terrain_height_generation(Default config, Vec3 worldCoords, float seed) {
  float terrainHeight = terrain_height(config, worldCoords, seed);

  terrainHeight += (small_scale_octave(worldCoords, seed) * plain_noise(worldCoords, seed));
  terrainHeight += (medium_scale_octave(worldCoords, seed) * mountain_noise(worldCoords, seed));
  terrainHeight += (lake_depression_octave(worldCoords, seed) * lake_depression_noise(worldCoords, seed));

  return terrainHeight;
}

static float small_scale_octave(Vec3 worldCoords, float seed) {
  const float frequency = 0.007f;
  const float amplitude = 5.f;

  return (noise2D(frequency * worldCoords.x, frequency * worldCoords.z, seed) * amplitude);
}

static float medium_scale_octave(Vec3 worldCoords, float seed) {
  const float frequency = 0.02f;
  const float amplitude = 20.f;

  return (noise2D(frequency * worldCoords.x, frequency * worldCoords.z, seed) * amplitude);
}

static float mountain_noise(Vec3 worldCoords, float seed) {
  return noise2D(worldCoords.x * 0.01f, worldCoords.z * 0.01f, seed);
}

static float plain_noise(Vec3 worldCoords, float seed) {
  return noise2D(worldCoords.x * 0.01f, worldCoords.z * 0.01f, seed);
}

static float lake_depression_octave(Vec3 worldCoords, float seed) {
  const float frequency = 0.01f;
  const float amplitude = -15.f;

  return noise2D(worldCoords.x * frequency, worldCoords.z * frequency, seed) * amplitude;
}

static float lake_depression_noise(Vec3 worldCoords, float seed) {
  return noise2D(worldCoords.x * 0.01f, worldCoords.z * 0.01f, seed);
}

Vegetation default_vegetation_generation(Default config, Vec3 worldCoords, float seed) {
  Vegetation vegetation;

  vegetation.position = worldCoords;
  vegetation.type = vegetation_get_type_by_noise_value(worldCoords, seed);

  return vegetation;
}

static float vegetation_noise(Vec3 worldCoords, float seed) {
  return noise2D(worldCoords.x * 0.09f, worldCoords.z * 0.09f, seed);
}

static float vegetation_type_noise(Vec3 worldCoords, float seed) {
  return noise2D(worldCoords.x * 0.03f, worldCoords.z * 0.03f, seed);
}

static VegetationType vegetation_get_type_by_noise_value(Vec3 worldCoords, float seed) {
  const float vegetationNoise = vegetation_noise(worldCoords, seed); 
  const float vegetationTypeNoise = vegetation_type_noise(worldCoords, seed);
  VegetationType vegetationType = VEGETATION_NONE;

  if(vegetationNoise < 0.1f) {
    float vegetationSingleProbability = 1.f / ((float)(VEGETATION_COUNT - 1)); 

    for(VegetationType i = VEGETATION_SHORT_GRASS; i < VEGETATION_COUNT; ++i) {
      if(vegetationTypeNoise <= ((float)i * vegetationSingleProbability + vegetationSingleProbability)) {
        vegetationType = i;
        break;
      }    
    }
  }

  return vegetationType;
}
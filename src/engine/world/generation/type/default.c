#include "default.h"

Default default_get_config() {
  Default config;

  config.maxHeight = world_config_get().worldMaxHeight;
  config.minHeight = world_config_get().worldMinHeight;
  config.baseTerrainHeight = 66.f;
  config.maxTerrainHeight = 128.f;
  config.amplitude = (config.maxTerrainHeight - config.baseTerrainHeight) - 40.f;
  config.frequency = 0.005f;
  config.waterMaxHeight = 66.f;

  return config;
}

Block default_get_block_on_y_level(Default config, float worldY) {
  if(worldY > config.maxTerrainHeight || worldY < config.minHeight) return BLOCK_AIR;
  if(worldY > config.maxTerrainHeight - 40.f) return BLOCK_STONE; 
  if(worldY > config.baseTerrainHeight) return BLOCK_GRASS;
  if(worldY > 2.f) return BLOCK_STONE;
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
  terrainHeight += lake_depression_octave(worldCoords, seed);

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
  return noise2D(worldCoords.x * 0.03f, worldCoords.z * 0.03f, seed);
}

static float plain_noise(Vec3 worldCoords, float seed) {
  return noise2D(worldCoords.x * 0.0008f, worldCoords.z * 0.0008f, seed);
}

static float lake_depression_octave(Vec3 worldCoords, float seed) {
  const float frequency = 0.01f;
  const float amplitude = -15.f;

  return noise2D(worldCoords.x * frequency, worldCoords.z * frequency, seed) * amplitude;
}
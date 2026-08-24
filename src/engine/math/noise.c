#include "noise.h"

float noise2D(float x, float z, int seed) {
  int32_t cellX = (int32_t)floor(x);
  int32_t cellZ = (int32_t)floor(z);

  float topLeft = random_from_position(cellX, cellZ, seed);
  float topRight = random_from_position(cellX + 1, cellZ, seed);
  float bottomLeft = random_from_position(cellX, cellZ + 1, seed);
  float bottomRight = random_from_position(cellX + 1, cellZ + 1, seed);

  float tx = fade(x - (float)cellX);
  float tz = fade(z - (float)cellZ);

  float topLerp = lerp(topLeft, topRight, tx);
  float bottomLerp = lerp(bottomLeft, bottomRight, tx);
  float noise = lerp(topLerp, bottomLerp, tz);

  return noise;
}

static uint32_t hash_position(int32_t x, int32_t z, int32_t seed) {
  uint32_t h = (uint32_t)seed;

  h ^= (uint32_t)x * 0x9E3779B9u;
  h ^= (uint32_t)z * 0x85EBCA6Bu;

  h ^= h >> 16;
  h *= 0x85EBCA6Bu;
  h ^= h >> 13;
  h *= 0xC2B2AE35u;
  h ^= h >> 16;

  return h;
}

static float random_from_position(int32_t x, int32_t z, int32_t seed) {
  uint32_t h = hash_position(x, z, seed);

  return (float)h / (float) UINT32_MAX;
}

static float lerp(float a, float b, float t) {
  return (a + (b - a) * t); 
}

static float fade(float t) {
  return t * t * t * (t * (t * 6.f - 15.f) + 10.f); 
}
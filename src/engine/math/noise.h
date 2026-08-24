#pragma once

#include <math.h>
#include <stdint.h>

float noise2D(float x, float z, int32_t seed);
static uint32_t hash_position(int32_t x, int32_t z, int32_t seed);
static float random_from_position(int32_t x, int32_t z, int32_t seed);
static float lerp(float a, float b, float t);
static float fade(float t);
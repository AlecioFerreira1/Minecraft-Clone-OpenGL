#include "vegetation_definition.h"

const VegetationDefinition REGISTERED_VEGETATIONS[VEGETATION_COUNT] = {
  [VEGETATION_SHORT_GRASS] = {
    .material = (Material) {
      .tile = (AtlasTile) {.tile_x = 8, .tile_y = 41}, 
      .color = (Color) {.r = 80.f / 255.f, .g = 149.f / 255.f, .b = 41.f / 255.f, .a = 1.f}, 
      .animated = false,
      .renderMode = RENDER_MODE_CUTOUT,
      .doubleSized = true
    },
    .solid = false,
  },
  [VEGETATION_TALL_GRASS] = {
    .material = (Material) {
      .tile = (AtlasTile) {.tile_x = 7, .tile_y = 41}, 
      .color = (Color) {.r = 80.f / 255.f, .g = 149.f / 255.f, .b = 41.f / 255.f, .a = 1.f}, 
      .animated = false,
      .renderMode = RENDER_MODE_CUTOUT,
      .doubleSized = true
    },
    .solid = false,
  },
  [VEGETATION_DEAD_BUSH] = {
    .material = (Material) {
      .tile = (AtlasTile) {.tile_x = 63, .tile_y = 22}, 
      .color = (Color) {.r = 1.f, .g = 1.f, .b = 1.f, .a = 1.f}, 
      .animated = false,
      .renderMode = RENDER_MODE_CUTOUT,
      .doubleSized = true
    },
    .solid = false,
  },
  [VEGETATION_DANDELION] = {
    .material = (Material) {
      .tile = (AtlasTile) {.tile_x = 63, .tile_y = 3}, 
      .color = (Color) {.r = 1.f, .g = 1.f, .b = 1.f, .a = 1.f}, 
      .animated = false,
      .renderMode = RENDER_MODE_CUTOUT,
      .doubleSized = true
    },
    .solid = false,
  },
  [VEGETATION_POPPY] = {
    .material = (Material) {
      .tile = (AtlasTile) {.tile_x = 6, .tile_y = 39}, 
      .color = (Color) {.r = 1.f, .g = 1.f, .b = 1.f, .a = 1.f}, 
      .animated = false,
      .renderMode = RENDER_MODE_CUTOUT,
      .doubleSized = true
    },
    .solid = false,
  },
  [VEGETATION_BLUE_ORCHID] = {
    .material = (Material) {
      .tile = (AtlasTile) {.tile_x = 60, .tile_y = 10}, 
      .color = (Color) {.r = 1.f, .g = 1.f, .b = 1.f, .a = 1.f}, 
      .animated = false,
      .renderMode = RENDER_MODE_CUTOUT,
      .doubleSized = true
    },
    .solid = false,
  },
  [VEGETATION_ALLIUM] = {
    .material = (Material) {
      .tile = (AtlasTile) {.tile_x = 57, .tile_y = 26}, 
      .color = (Color) {.r = 1.f, .g = 1.f, .b = 1.f, .a = 1.f}, 
      .animated = false,
      .renderMode = RENDER_MODE_CUTOUT,
      .doubleSized = true
    },
    .solid = false,
  },
  [VEGETATION_AZURE_BLUET] = {
    .material = (Material) {
      .tile = (AtlasTile) {.tile_x = 57, .tile_y = 32}, 
      .color = (Color) {.r = 1.f, .g = 1.f, .b = 1.f, .a = 1.f}, 
      .animated = false,
      .renderMode = RENDER_MODE_CUTOUT,
      .doubleSized = true
    },
    .solid = false,
  },
  [VEGETATION_RED_TULIP] = {
    .material = (Material) {
      .tile = (AtlasTile) {.tile_x = 50, .tile_y = 39}, 
      .color = (Color) {.r = 1.f, .g = 1.f, .b = 1.f, .a = 1.f}, 
      .animated = false,
      .renderMode = RENDER_MODE_CUTOUT,
      .doubleSized = true
    },
    .solid = false,
  },
  [VEGETATION_ORANGE_TULIP] = {
    .material = (Material) {
      .tile = (AtlasTile) {.tile_x = 46, .tile_y = 38}, 
      .color = (Color) {.r = 1.f, .g = 1.f, .b = 1.f, .a = 1.f}, 
      .animated = false,
      .renderMode = RENDER_MODE_CUTOUT,
      .doubleSized = true
    },
    .solid = false,
  },
  [VEGETATION_WHITE_TULIP] = {
    .material = (Material) {
      .tile = (AtlasTile) {.tile_x = 43, .tile_y = 41}, 
      .color = (Color) {.r = 1.f, .g = 1.f, .b = 1.f, .a = 1.f}, 
      .animated = false,
      .renderMode = RENDER_MODE_CUTOUT,
      .doubleSized = true
    },
    .solid = false,
  },
  [VEGETATION_PINK_TULIP] = {
    .material = (Material) {
      .tile = (AtlasTile) {.tile_x = 59, .tile_y = 38}, 
      .color = (Color) {.r = 1.f, .g = 1.f, .b = 1.f, .a = 1.f}, 
      .animated = false,
      .renderMode = RENDER_MODE_CUTOUT,
      .doubleSized = true
    },
    .solid = false,
  },
  [VEGETATION_OXEYE_DAISY] = {
    .material = (Material) {
      .tile = (AtlasTile) {.tile_x = 48, .tile_y = 38}, 
      .color = (Color) {.r = 1.f, .g = 1.f, .b = 1.f, .a = 1.f}, 
      .animated = false,
      .renderMode = RENDER_MODE_CUTOUT,
      .doubleSized = true
    },
    .solid = false,
  },
  [VEGETATION_OAK_TREE] = {
    .material = (Material) {
      .tile = (AtlasTile) {.tile_x = 0, .tile_y = 0}, 
      .color = (Color) {.r = 1.f, .g = 1.f, .b = 1.f, .a = 0.f}, 
      .animated = false,
      .renderMode = RENDER_MODE_OPAQUE,
      .doubleSized = false
    },
    .solid = true,
  },
};
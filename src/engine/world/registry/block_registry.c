#include "block_registry.h"

const BlockDefinition REGISTERED_BLOCKS[BLOCK_COUNT] = {
  [BLOCK_AIR] = (BlockDefinition){
    (AtlasTile) {0, 0},
    (AtlasTile) {0, 0},
    (AtlasTile) {0, 0},
    (AtlasTile) {0, 0},
    (AtlasTile) {0, 0},
    (AtlasTile) {0, 0},
    true,
    false
  },
  [BLOCK_GRASS] = (BlockDefinition){
    (AtlasTile) {38, 36},
    (AtlasTile) {64, 11},
    (AtlasTile) {22, 36},
    (AtlasTile) {22, 36},
    (AtlasTile) {22, 36},
    (AtlasTile) {22, 36},
    false,
    true
  },
  [BLOCK_STONE] = (BlockDefinition){
    (AtlasTile) {40, 40},
    (AtlasTile) {40, 40},
    (AtlasTile) {40, 40},
    (AtlasTile) {40, 40},
    (AtlasTile) {40, 40},
    (AtlasTile) {40, 40},
    false,
    true
  },
  [BLOCK_DIRT] = (BlockDefinition){ 
    (AtlasTile) {64, 11},
    (AtlasTile) {64, 11},
    (AtlasTile) {64, 11},
    (AtlasTile) {64, 11},
    (AtlasTile) {64, 11},
    (AtlasTile) {64, 11},
    false,
    true
  },
  [BLOCK_TNT] = (BlockDefinition){ 
    (AtlasTile) {14, 41},
    (AtlasTile) {12, 41},
    (AtlasTile) {13, 41},
    (AtlasTile) {13, 41},
    (AtlasTile) {13, 41},
    (AtlasTile) {13, 41},
    false,
    true
  },
};
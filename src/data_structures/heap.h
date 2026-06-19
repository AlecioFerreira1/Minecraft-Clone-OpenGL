#pragma once
#include "vector.h"

typedef struct {
  Vector data;
  int8_t (*compare)(const void *itemA, const void *itemB);
  size_t element_size;
  void *tmpBuffer;
} Heap;

Heap heap_create(size_t element_size, int8_t (*compare)(const void *itemA, const void *itemB));
void heap_destroy(Heap *heap);
void heap_insert(Heap *heap, void *item);
static void sift_up(Heap *heap);
static void sift_down(Heap *heap, size_t startIndex);
void *heap_extract(Heap *heap);
void *heap_peek(const Heap *heap);
void heap_build(Heap *heap, const Vector *vector, int8_t (*compare)(const void *itemA, const void *itemB));
static void swap(void *itemA, void *itemB, void *tmp, size_t element_size);
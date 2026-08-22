#pragma once

#include "heap.h"

typedef struct {
  Heap heap;
} PriorityQueue;

PriorityQueue priority_queue_create(size_t element_size, int8_t (*compare)(const void *itemA, const void *itemB));
void priority_queue_destroy(PriorityQueue *queue);
void priority_queue_push(PriorityQueue *queue, void *item);
void priority_queue_pop(PriorityQueue *queue);
bool priority_queue_is_empty(const PriorityQueue *queue);
void *priority_queue_peek(const PriorityQueue *queue);
PriorityQueue priority_queue_build_from_vector(const Vector *vector, int8_t (*compare)(const void *itemA, const void *itemB));
void priority_queue_clear(PriorityQueue *queue);
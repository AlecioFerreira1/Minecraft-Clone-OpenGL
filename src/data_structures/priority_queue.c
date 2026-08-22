#include "priority_queue.h"

PriorityQueue priority_queue_create(size_t element_size, int8_t (*compare)(const void *itemA, const void *itemB)) {
  PriorityQueue queue;

  queue.heap = heap_create(element_size, compare);

  return queue;
}

void priority_queue_destroy(PriorityQueue *queue) {
  heap_destroy(&queue->heap);
}


void priority_queue_push(PriorityQueue *queue, void *item) {
  heap_insert(&queue->heap, item);
}

void priority_queue_pop(PriorityQueue *queue) {
  heap_extract(&queue->heap);
}

bool priority_queue_is_empty(const PriorityQueue *queue) {
  return vector_is_empty(&queue->heap.data);
}

void* priority_queue_peek(const PriorityQueue *queue) {
  return heap_peek(&queue->heap);
}

PriorityQueue priority_queue_build_from_vector(const Vector *vector, int8_t (*compare)(const void *itemA, const void *itemB)) {
  PriorityQueue queue;

  heap_build(&queue.heap, vector, compare);

  return queue;
}

void priority_queue_clear(PriorityQueue *queue) {
  vector_clear(&queue->heap.data);
}
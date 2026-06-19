#include "heap.h"

Heap heap_create(size_t element_size, int8_t (*compare)(const void *itemA, const void *itemB)) {
  Heap heap;

  heap.compare = compare;
  heap.element_size = element_size;
  heap.data = vector_create(VECTOR_MIN_CAPACITY, element_size);
  heap.tmpBuffer = malloc(element_size);

  return heap;
}

void heap_destroy(Heap *heap) {
  vector_destroy(&heap->data);

  heap->compare = NULL;
  heap->element_size = 0;

  free(heap->tmpBuffer);
}

void heap_insert(Heap *heap, void *item) {
  vector_push_back(&heap->data, item);
  sift_up(heap);
}

static void sift_up(Heap *heap) {
  const size_t vectorSize = vector_size(&heap->data);

  for(size_t i = vectorSize - 1; i > 0; i = (i - 1) / 2) {
    void *currentItem = vector_get_item(&heap->data, i);
    void *parent = vector_get_item(&heap->data, (i - 1) / 2);

    if(heap->compare(parent, currentItem) > 0) {
      swap(parent, currentItem, heap->tmpBuffer, heap->element_size);
    }

    else break;
  }
}

static void sift_down(Heap *heap, size_t startIndex) {
  const size_t vectorSize = vector_size(&heap->data);
  size_t i = startIndex;

  if(vectorSize == 0) return;

  for( ; ; ) {
    void *currentItem = vector_get_item(&heap->data, i);
    void *toSwap = currentItem;
    size_t index = i;

    if(2 * i + 1 < vectorSize) {
      void *leftChild = vector_get_item(&heap->data, 2 * i + 1);

      if(heap->compare(currentItem, leftChild) > 0) {
        toSwap = leftChild;
        index = 2 * i + 1;
      }
    }
  
    if(2 * i + 2 < vectorSize) {
      void *rightChild = vector_get_item(&heap->data, 2 * i + 2);

      if(heap->compare(toSwap, rightChild) > 0) {
        toSwap = rightChild;
        index = 2 * i + 2;
      }
    }

    if(toSwap == currentItem) break;
    swap(currentItem, toSwap, heap->tmpBuffer, heap->element_size);
    i = index;
  }
}

void *heap_extract(Heap *heap) {
  void *root = vector_front(&heap->data);
  void *last = vector_back(&heap->data);

  swap(root, last, heap->tmpBuffer, heap->element_size);
  vector_pop_back(&heap->data);
  sift_down(heap, 0);

  return heap->tmpBuffer;
}

void *heap_peek(const Heap *heap) {
  return vector_get_item(&heap->data, 0);
}

void heap_build(Heap *heap, const Vector *vector, int8_t (*compare)(const void *itemA, const void *itemB)) {
  heap->compare = compare;
  heap->data = vector_copy(vector);
  heap->element_size = vector->element_size;
  heap->tmpBuffer = malloc(vector->element_size);

  const long long vectorSize = (long long) vector_size(&heap->data);

  for(long long i = (vectorSize / 2) - 1; i >= 0; --i) {
    sift_down(heap, i);
  }
}

static void swap(void *itemA, void *itemB, void *tmp, size_t element_size) {
  memcpy(tmp, itemA, element_size);
  memcpy(itemA, itemB, element_size);
  memcpy(itemB, tmp, element_size);
}
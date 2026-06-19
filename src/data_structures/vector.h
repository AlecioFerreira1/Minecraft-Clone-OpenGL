#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define VECTOR_MIN_CAPACITY 10

typedef struct {
  size_t capacity;
  size_t size;
  size_t element_size;
  void *data;
} Vector;

Vector vector_create(size_t initialCapacity, size_t element_size);
void vector_destroy(Vector *vector);
void vector_clear(Vector *vector);
static bool vector_has_capacity(const Vector *vector);
static void vector_realloc_space(Vector *vector);
void vector_push_back(Vector *vector, void *item);
void vector_push_front(Vector *vector, void *item);
void vector_push_at(Vector *vector, size_t index, void *item);
void *vector_get_item(const Vector *vector, size_t index);
void vector_remove_at(Vector *vector, size_t index);
void vector_pop_back(Vector *vector);
void vector_pop_front(Vector *vector);
size_t vector_size(const Vector *vector);
bool vector_is_empty(const Vector *vector);
void *vector_back(const Vector *vector);
void *vector_front(const Vector *vector);
void vector_set_item(Vector *vector, size_t index, void *item);
Vector vector_copy(const Vector *vector);
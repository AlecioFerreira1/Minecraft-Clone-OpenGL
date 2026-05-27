#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

typedef enum {
  HASH_MAP_ENTRY_STATE_EMPTY, 
  HASH_MAP_ENTRY_STATE_OCCUPIED, 
  HASH_MAP_ENTRY_STATE_DELETED
} State;

typedef struct {
  char* key;
  void* value;
  State state;
} Entry;

typedef struct {
  size_t capacity;
  size_t quant; 
  Entry* elements;
} HashMap;

void hash_map_create(HashMap* table, size_t size);
void hash_map_insert(HashMap* table, char* key, void* value);
long long hash_map_search(HashMap* table, char* key);
void* hash_map_get_value(HashMap* table, char* key);
void hash_map_delete_key(HashMap* table, char* key);
static void rehashing(HashMap* table, char option);
static int hash_func(int key, int k, size_t size);
static void copy_table(HashMap* dstTable, HashMap* srcTable);
void hash_map_destroy(HashMap* table);
static unsigned long hash_string(char* str);
static long long nearest_prime(long long num);
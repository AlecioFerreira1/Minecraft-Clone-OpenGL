#include "hash_map.h"

static const char REHASHING_INCREASE = 'I';
static const char REHASHING_DECREASE = 'D';

void hash_map_create(HashMap* table, size_t size) {
  table->quant = 0;
  table->capacity = size;
  table->elements = (Entry*) malloc(sizeof(Entry) * table->capacity);
  
  for(size_t i = 0; i < table->capacity; ++i){
    table->elements[i].key = NULL;
    table->elements[i].value = NULL;
    table->elements[i].state = HASH_MAP_ENTRY_STATE_EMPTY;
  }
}

void hash_map_insert(HashMap* table, char* key, void* value) {
  const float LOAD_FACTOR = 0.6f;

  if(((float) table->quant / (float) table->capacity) > LOAD_FACTOR){
    rehashing(table, REHASHING_INCREASE); 
  }

  size_t index = hash_string(key) % table->capacity;
  size_t tries = 1;
  bool keyAlreadyUsed = false;

  while(table->elements[index].key != NULL){
    if(strcmp(table->elements[index].key, key) == 0){
      keyAlreadyUsed = true;
      break; 
    }

    index = hash_func(index, tries, table->capacity);
    tries++;
  }

  if(!keyAlreadyUsed){
    table->quant++;
  }

  table->elements[index].key = key;
  table->elements[index].value = value;
  table->elements[index].state = HASH_MAP_ENTRY_STATE_OCCUPIED;
}

long long hash_map_search(HashMap* table, char* key) {
  size_t index = hash_string(key) % table->capacity;
  size_t tries = 1;
  bool keyFound = false;

  if(table->elements[index].key != NULL){
    keyFound = strcmp(table->elements[index].key, key) == 0;
  }

  while(tries < table->capacity){
    if(keyFound || table->elements[index].state == HASH_MAP_ENTRY_STATE_EMPTY) break;

    index = hash_func(index, tries, table->capacity);
    keyFound = strcmp(table->elements[index].key, key) == 0;
    tries++;
  }

  if(keyFound){
    return (long long) index;
  }

  return -1;
}

void* hash_map_get_value(HashMap* table, char* key) {
  long long index = hash_map_search(table, key);

  if(index == -1) return NULL;

  return table->elements[index].value;
}

void hash_map_delete_key(HashMap* table, char* key) {
  int index = hash_map_search(table, key);

  if(index == -1) {
    printf("DELETION ERROR. KEY NOT FOUND! KEY: %s", key);
    return;
  }

  table->elements[index].key = NULL;
  table->elements[index].state = HASH_MAP_ENTRY_STATE_DELETED;
  table->elements[index].value = NULL;
  table->quant--;

  if(((float) table->quant / (float) table->capacity) < 0.25f){
    rehashing(table, REHASHING_DECREASE);
  }
}

static void rehashing(HashMap* table, char option) {
  int size = 0;

  if(option == REHASHING_INCREASE){
    size = nearest_prime((long long) (table->capacity * 2));
  }

  else{
    size = nearest_prime((long long) (table->capacity * 0.6));
  }

  HashMap newTable;

  hash_map_create(&newTable, size);
  copy_table(&newTable, table);
  hash_map_destroy(table);

  *table = newTable;
}

static int hash_func(int key, int k, size_t size) {
  return ((key % size) + k) % size;
}

static void copy_table(HashMap* dstTable, HashMap* srcTable) {
  for(size_t i = 0; i < srcTable->capacity; ++i){
    if(srcTable->elements[i].key != NULL){
      hash_map_insert(dstTable, srcTable->elements[i].key, srcTable->elements[i].value);
    }
  }
}

void hash_map_destroy(HashMap* table) {
  free(table->elements);
}

static unsigned long hash_string(char* str) {
  unsigned long hash = 5381;

  while(*str) {
    hash = ((hash << 5) + hash) + *str;
    *str++;
  }

  return hash;
}

static long long nearest_prime(long long num) { 
  if(num <= 2) return 2;
  if(num == 3) return 3;

  bool isPrime = false;
  long long primeNum = num;

  while(!isPrime){
    isPrime = true;

    long long sqrtNum = ((long long)(sqrtl(primeNum)));

    for(long long i = 2; i <= sqrtNum; ++i){
      if(primeNum % i == 0) {
        primeNum++;
        isPrime = false;
        break;      
      }
    }
  }

  return primeNum;
}
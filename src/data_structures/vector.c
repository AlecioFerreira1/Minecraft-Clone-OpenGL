#include "vector.h"

Vector vector_create(size_t initialCapacity, size_t element_size) {
  Vector vector;

  vector.capacity = initialCapacity;
  vector.size = 0;
  vector.element_size = element_size;
  vector.data = malloc(element_size * initialCapacity);

  if(vector.data == NULL) {
    printf("\nERRO DE ALOCACAO DE MEMORIA! ERRO EM VECTOR_CREATE!\n");
    exit(-1);
  }

  return vector;
}

void vector_destroy(Vector *vector) {
  free(vector->data);

  vector->data = NULL;
  vector->size = 0;
  vector->capacity = 0;
  vector->element_size = 0;
}

void vector_clear(Vector *vector) {
  size_t element_size = vector->element_size;

  vector_destroy(vector);
  *vector = vector_create(VECTOR_MIN_CAPACITY, element_size);
}

static bool vector_has_capacity(const Vector *vector) {
  return vector->capacity >= (vector->size + 1);
}

static void vector_realloc_space(Vector *vector, bool increase) {
  double multiplier = increase ? 2.0 : 0.5;
  size_t size = (size_t) (multiplier * vector->capacity);

  vector_reserve(vector, size);
}

void vector_push_back(Vector *vector, void *item) {
  vector_push_at(vector, vector->size, item);
} 

void vector_push_front(Vector *vector, void *item) {
  vector_push_at(vector, 0, item);
}

void vector_push_at(Vector *vector, size_t index, void *item) {
  if(index > vector->size) {
    index = vector->size;
  }

  if(!vector_has_capacity(vector)) {
    vector_realloc_space(vector, true);   
  }

  unsigned char *dst = (unsigned char *) vector->data;
  size_t n = (vector->size - index) * vector->element_size;

  dst = dst + (index * vector->element_size);

  memmove(dst + vector->element_size, dst, n);
  memcpy(dst, item, vector->element_size);

  vector->size++;
}

void *vector_get_item(const Vector *vector, size_t index) {
  if(index >= vector->size) {
    printf("\nERRO AO RESGATAR O ITEM NO INDICE '%zu'. FORA DOS LIMITES!\n", index);
    return NULL;
  }

  unsigned char *vectorBytes = (unsigned char *) vector->data;

  return vectorBytes + (index * vector->element_size);
}

void vector_remove_at(Vector *vector, size_t index) {
  if(index >= vector->size) {
    printf("\nERRO AO REMOVER O ITEM NO INDICE '%zu'. FORA DOS LIMITES!\n", index);
    return;
  }

  if(((double)vector->size / (double)vector->capacity) < 0.3) {
    vector_realloc_space(vector, false);
  }

  unsigned char *dst = (unsigned char *) vector->data;
  size_t n = (vector->size - index) * vector->element_size; 

  dst = dst + (index * vector->element_size);

  memmove(dst, dst + vector->element_size, n);

  vector->size--;
}

void vector_pop_back(Vector *vector) {
  vector_remove_at(vector, vector->size - 1);
}

void vector_pop_front(Vector *vector) {
  vector_remove_at(vector, 0);
}

size_t vector_size(const Vector *vector) {
  return vector->size;
}

bool vector_is_empty(const Vector *vector) {
  return vector->size == 0;
}

void *vector_back(const Vector *vector) {
  return vector_get_item(vector, vector->size - 1); 
}

void *vector_front(const Vector *vector) {
  return vector_get_item(vector, 0);
}

void vector_set_item(Vector *vector, size_t index, void *item) {
  if(index >= vector->size) {
    printf("\nERRO AO SUBSTITUIR O ITEM NO INDICE '%zu'. FORA DOS LIMITES!\n.", index);
    return;
  }

  unsigned char *pos = (unsigned char *) vector->data;

  pos = pos + (index * vector->element_size);

  memcpy(pos, item, vector->element_size);
}

Vector vector_copy(const Vector *vector) {
  Vector newVector = vector_create(vector->capacity, vector->element_size);
  
  memcpy(newVector.data, vector->data, vector->element_size * vector->size);
  
  newVector.size = vector->size;

  return newVector;
}

void vector_append_many(Vector *dst, const Vector *src) {
  if(dst->element_size != src->element_size) {
    printf("\nERRO AO ADICIONAR OS ITENS! OS TIPOS DE VECTOR SÃO DIFERENTES!\n");
    return;
  }

  if((dst->capacity - dst->size) < src->size) {
    vector_reserve(dst, dst->capacity + src->size);
  }

  unsigned char *lastItem = (unsigned char *) dst->data;

  lastItem += dst->size * dst->element_size;

  memcpy(lastItem, src->data, src->size * src->element_size);

  dst->size += src->size;
}

void vector_reserve(Vector *vector, size_t reservedSize) {
  if(reservedSize < vector->size) {
    printf("ERRO AO RESERVAR MEMÓRIA PARA O VECTOR, O VALOR SOLICITADO CAUSA PERDA DE DADOS.\n");
    printf("INSIRA UM VALOR MAIOR DO QUE A QUANTIDADE DE ITENS DO VECTOR! TAMANHO DO VECTOR: %zu\n", vector->size);
    return;
  }

  void *tmp = realloc(vector->data, reservedSize * vector->element_size);
  
  if(tmp != NULL) {
    vector->capacity = reservedSize;
    vector->data = tmp;
    return;
  }

  printf("\nERRO DE ALOCACAO DE MEMORIA! ERRO EM VECTOR_RESERVE!\n");
  exit(-1);
}
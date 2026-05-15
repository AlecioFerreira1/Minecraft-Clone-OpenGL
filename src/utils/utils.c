#include "utils.h"

char* readFile(const char* filePath){
  FILE* file = fopen(filePath, "rb");

  if(file == NULL) return NULL;

  fseek(file, 0, SEEK_END);

  long size = ftell(file);

  rewind(file);
    
  char* buffer = (char *) malloc(size + 1);

  size_t bytesRead = fread(buffer, 1, size, file);
  buffer[bytesRead] = '\0';

  fclose(file);

  return buffer;
}
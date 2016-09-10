#pragma once
#include <stddef.h>

#define LRU_PRINT_STRING 256

typedef struct { 
  int key;
  struct node_t* next;
} node_t;

typedef struct { 
  node_t* head;
  node_t* tail;
} lru_t;

void lru_init(lru_t*, size_t);
void lru_insert(lru_t*, int);
void lru_print(lru_t*, char*);

#pragma once
#include <stddef.h>

#define LRU_PRINT_STRING 256

struct node_t;  
typedef struct node_t node_t;  

struct lru_t;  
typedef struct lru_t lru_t;

void lru_init(lru_t**, size_t);
int lru_insert(lru_t*, int);
void lru_print(lru_t*, char**);
void lru_destroy(lru_t*);

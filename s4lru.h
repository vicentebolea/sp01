#pragma once
#include <stddef.h>

struct s4lru_t;
typedef struct s4lru_t s4lru_t;

void s4lru_init(s4lru_t**, size_t);
int s4lru_insert(s4lru_t*, int);
void s4lru_visitor(s4lru_t*);
void s4lru_destroy(s4lru_t*);
void s4lru_resize(s4lru_t*, size_t);

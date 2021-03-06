#include "s4lru.h"
#include "lru.h"
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

#define S4LRU_NUM 4

struct s4lru_t {
  lru_t** lru_array;
  FILE* fd[S4LRU_NUM];
};

void s4lru_init(s4lru_t** lru, size_t size) {
  *lru = calloc(1, sizeof(s4lru_t));
  (*lru)->lru_array = calloc(S4LRU_NUM, sizeof(lru_t*));

  int i; 
  for (i = 0; i < S4LRU_NUM; i++) {
    lru_init(&(*lru)->lru_array[i], size);
  }

  (*lru)->fd[0] = fopen("list_0.txt", "w");
  (*lru)->fd[1] = fopen("list_1.txt", "w");
  (*lru)->fd[2] = fopen("list_2.txt", "w");
  (*lru)->fd[3] = fopen("list_3.txt", "w");
}

static int s4lru_recursive_evict(s4lru_t* lru, int current, int input)  {
  assert(current >= 0);

  if (current == 0) { // Base case
    return lru_insert(lru->lru_array[0], input);
  
  } else {
    int evicted = lru_insert(lru->lru_array[current], input);
    if (evicted != INT_MIN)
      return s4lru_recursive_evict(lru, current-1, evicted);
  }
  return INT_MIN;
}

/*
 * Precondition: input >= 0
 */
int s4lru_insert(s4lru_t* lru, int input) {
  assert(input >= 0); 

  int i; 
  node_t* node;
  for (i = 0; i < S4LRU_NUM ; i++) {
    node = lru_search(lru->lru_array[i], input);
    if (node) break;
  }

  if (node != NULL) {  //! If we have found the key 
    node_t* to_free = lru_remove(lru->lru_array[i], input);
    free(to_free);

    int evicted_key;
    if (i == S4LRU_NUM-1) { // If we are at the top lru
      evicted_key = lru_insert(lru->lru_array[i], input);
    } else {
      evicted_key = lru_insert(lru->lru_array[i+1], input);
    }

    if (evicted_key != INT_MIN)  //! If we have to evict
      s4lru_recursive_evict(lru, i, evicted_key);

  } else {  // If it is not found
    int evicted = lru_insert(lru->lru_array[0], input);
    return evicted;
  }

  return INT_MIN;
}

void s4lru_visitor(s4lru_t* lru) {
  int i; 
  for (i = 0; i < S4LRU_NUM; i++) {
    lru_visitor(lru->lru_array[i], lru->fd[i]);
  }
}

void s4lru_resize(s4lru_t* lru, size_t size) {
  int i; 
  for (i = 0; i < S4LRU_NUM; i++) {
    lru_resize(lru->lru_array[i], size);
  }
}

void s4lru_destroy(s4lru_t* lru) {
  int i; 
  for (i = 0; i < S4LRU_NUM; i++) {
    lru_destroy(lru->lru_array[i]);
  }
  free(lru->lru_array);

  fclose(lru->fd[0]);
  fclose(lru->fd[1]);
  fclose(lru->fd[2]);
  fclose(lru->fd[3]);
  free(lru);
}

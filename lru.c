#include "lru.h"
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>

struct node_t { 
  int key;
  node_t* next;
};

struct lru_t { 
  node_t* head;
  node_t* tail;
  size_t size;
}; 

/*
 *
 */
static bool is_full (lru_t* lru) {
  node_t* node = lru->head;
  size_t current_size = 0;

  while (node) {
    node = node->next;
    current_size++;
  }

  return (lru->size <= current_size);
}

/*
 *
 */
static int evict_node(lru_t* lru) {
  assert(lru->size > 1);
  int evicted_value = 0;

  node_t* node = lru->head;
  while (node->next->next) {
    node = node->next;
  }

  evicted_value = node->next->key; 
  free(lru->tail);
  lru->tail = node;
  node->next = NULL;
  return evicted_value;
}

/*
 *
 */
static void insert_head(lru_t* lru, node_t* node) {
  node_t* tmp = lru->head;
  lru->head = node;
  lru->head->next = tmp;
}

/*
 *
 */
static node_t* extract(lru_t* lru, int input) {
  node_t* node = lru->head;
  node_t* previous_node = NULL;

  while (node) {
    if (node->key == input) {
      node_t* tmp = node->next;

      if (previous_node != NULL) {
        previous_node->next = tmp;
        if (lru->tail == node) {
          lru->tail = previous_node;
        }
      }
      return node;
    }
    previous_node = node;
    node = node->next;
  }
  return NULL;
}

/*
 *
 */
void lru_init(lru_t** lru, size_t size) {
  *lru = (lru_t*)calloc(1,sizeof(lru_t));
  (*lru)->size = size;
  (*lru)->head = (*lru)->tail = NULL;
}

/*
 *
 */
int lru_insert(lru_t* lru, int input) {
  int evicted_key = INT_MIN;

  node_t* node = NULL;
  if ((node = extract(lru, input))) {
    insert_head(lru, node);

  } else {
    if (is_full(lru))
      evicted_key = evict_node(lru);

    node = malloc(sizeof(node_t));
    node->key = input;

    if (!lru->head) {
      lru->tail = node;
      node->next = NULL;
    }

    insert_head(lru, node);
  }
  return evicted_key;
}

/*
 *
 */
void lru_visitor(lru_t* lru, void(*f)(void*, const char*), void* arg) {
  char line[LRU_PRINT_STRING] = {0};

  node_t* node = lru->head;
  for (; node; node = node->next)
    sprintf(line, "%s%d ", line, node->key);

  line[strlen(line) - 1] = '\0';
  f(arg, line);
}

/*
 *
 */
void lru_destroy(lru_t* lru) {
  free(lru);
}

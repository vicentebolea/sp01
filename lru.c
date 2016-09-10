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

static bool is_full (lru_t* lru) {
  node_t* node = lru->head;
  size_t current_size = 0;

  while (node) {
    node = node->next;
    current_size++;
  }

  return (lru->size <= current_size);
}

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

static bool find_and_insert(lru_t* lru, int input) {
  node_t* node = lru->head;

  node_t* previous_node = NULL;
  while (node) {

    if (node->key == input) {
      node_t* tmp = node->next;

      node_t* tmp2 = lru->head;
      lru->head = node;
      lru->head->next = tmp2;

      if (previous_node != NULL) {
        previous_node->next = tmp;
        if (lru->tail == node) {
          lru->tail = previous_node;
        }
      }

      return true;

    }
    previous_node = node;
    node = node->next;
  }
  return false;
}

void lru_init(lru_t** lru, size_t size) {
  *lru = (lru_t*)calloc(1,sizeof(lru_t));
  (*lru)->size = size;
  (*lru)->head = (*lru)->tail = NULL;
}

int lru_insert(lru_t* lru, int input) {
  int evicted_key = INT_MIN;
  if (lru->head == NULL) {
    lru->head = lru->tail = malloc(sizeof(node_t));
    lru->head->next = NULL;
    lru->head->key = input;

  } else if (!find_and_insert(lru, input)) {
    if (is_full(lru)) {
      evicted_key = evict_node(lru);
    }

    node_t* tmp = lru->head;
    lru->head = malloc(sizeof(node_t));
    lru->head->next = tmp;
    lru->head->key = input;
  }
  return evicted_key;
}

void lru_print(lru_t* lru, char** line) {
  node_t* node = lru->head;
  bzero(*line, LRU_PRINT_STRING);

  while (node) {
    char str[15];
    sprintf(str, "%d ", node->key);
    strcat(*line, str);
    node = node->next;
  }
}

void lru_destroy(lru_t* lru) {
  free(lru);
}

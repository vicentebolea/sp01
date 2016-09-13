/*
 * Author: Vicente Adolfo Bolea Sanchez 
 * Date: Sep'16
 * File: The following functions represent the public interface
 * of the ADT of a LRU.
 *
 * Usage: 
 *  lru_t* my_lru;
 *  lru_init(&my_lru);
 *  lru_insert(my_lru, 1);
 *  lru_insert(my_lru, 2);
 *  lru_insert(my_lru, 3);
 *  lru_remove(my_lru, 2);
 *  node_t* = lru_search(my_lru, 1);
 *  lru_destroy(my_lru);
 *
 */
#pragma once
#include <stddef.h>
#include <stdio.h>

#define LRU_PRINT_STRING 256

// Hiding structures content to fullfill the
// principle of least privilege
struct node_t;
typedef struct node_t node_t;  

struct lru_t;  
typedef struct lru_t lru_t;

void lru_init(lru_t**, size_t);
int lru_insert(lru_t*, int);
void lru_visitor(lru_t*, FILE*);
void lru_destroy(lru_t*);
void lru_resize(lru_t*, size_t);
node_t* lru_search(lru_t*, int);
node_t* lru_remove(lru_t*, int);

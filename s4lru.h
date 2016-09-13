/*
 * Author: Vicente Adolfo Bolea Sanchez 
 * Date: Sep'16
 * File: The following functions represent the public interface
 * of the ADT of a S4LRU.
 *
 * Usage: 
 *  s4lru_t* my_lru;
 *  s4lru_init(&my_lru);
 *  s4lru_insert(my_lru, 1);
 *  s4lru_insert(my_lru, 2);
 *  s4lru_insert(my_lru, 3);
 *  s4lru_remove(my_lru, 2);
 *  node_t* = s4lru_search(my_lru, 1);
 *  s4lru_destroy(my_lru);
 *
 */
#pragma once
#include <stddef.h>

struct s4lru_t;
typedef struct s4lru_t s4lru_t;

void s4lru_init(s4lru_t**, size_t);
int s4lru_insert(s4lru_t*, int);
void s4lru_visitor(s4lru_t*);
void s4lru_resize(s4lru_t*, size_t);
void s4lru_destroy(s4lru_t*);

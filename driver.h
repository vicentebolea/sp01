#pragma once
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

#define FILENAME_SIZE 256

typedef struct {
  char input_file[FILENAME_SIZE];
  char output_file[FILENAME_SIZE];
  char evict_file[FILENAME_SIZE];
  FILE* output_file_ptr;
  FILE* input_file_ptr;
  FILE* evict_file_ptr;
  size_t lru_size;
} options_t;

void driver_init(options_t*, int, char**);
bool is_next(options_t*);
int next_input(options_t*);
int get_lru_size(options_t*);
void print_lru_keys_to_file(options_t*, const char*);
void print_lru_evicted_to_file(options_t*, int);
void driver_close(options_t*);

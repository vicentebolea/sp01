#pragma once
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct {
  char input_file[FILENAME_MAX];
  char output_file[FILENAME_MAX];
  char evict_file[FILENAME_MAX];
  FILE* output_file_ptr;
  FILE* input_file_ptr;
  FILE* evict_file_ptr;
  size_t lru_size;
} options_t;

void driver_init(options_t*, int, char**);
bool is_next(options_t*);
int next_input(options_t*);
int driver_lru_size(options_t*);
void driver_log_keys(void*, const char*);
void driver_log_evicted_keys(void*, int);
void driver_close(options_t*);

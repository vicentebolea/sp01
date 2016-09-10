#pragma once
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

#define FILENAME_SIZE 256

typedef struct {
  char input_file[FILENAME_SIZE];
  char output_file[FILENAME_SIZE];
  FILE* output_file_ptr;
  size_t lru_size;
} options_t;

void parse_args(int, char**, options_t*);
void load_file(const char*);
void save_output(const char*);
bool is_next(options_t*);
int next_input(options_t*);

#include "driver.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>

struct options_t {
  char input_file[FILENAME_MAX];
  char output_file[FILENAME_MAX];
  char evict_file[FILENAME_MAX];
  FILE* output_file_ptr;
  FILE* input_file_ptr;
  FILE* evict_file_ptr;
  size_t lru_size;
};

void driver_init(options_t** ops, int argc, char** argv, const char* of, const char* ef) {
  if (argc != 3) {
    perror("Relaunch with args [size of lru] inputfile");
    exit(EXIT_FAILURE);
  }

  *ops = calloc(1, sizeof(options_t));
  (*ops)->lru_size = atoi(argv[1]);
  strncpy((*ops)->input_file, argv[2], FILENAME_MAX);

  strncpy(ops->output_file, of, FILENAME_MAX);
  strncpy(ops->output_file, ef, FILENAME_MAX);
  (*ops)->input_file_ptr = fopen((*ops)->input_file, "r");
  (*ops)->output_file_ptr = fopen((*ops)->output_file, "w");
  (*ops)->evict_file_ptr = fopen((*ops)->evict_file, "w");
}

bool is_next(options_t* ops) {
  bool flag = true;
  if (feof(ops->input_file_ptr))
    flag = false;

  else {
    char achar = fgetc(ops->input_file_ptr);
    if (feof(ops->input_file_ptr))
      flag = false;

    ungetc(achar, ops->input_file_ptr);
  }
  
  return flag;
}

int next_input(options_t* ops) { 
  char input[16] = {0};
  fgets(input, 16, ops->input_file_ptr);
  return atoi(input);
}

int driver_lru_size(options_t* ops) { 
  return ops->lru_size;
}

void driver_set_output_file(options_t* ops, const char* fn) {
  strncpy(ops->output_file, fn, FILENAME_MAX);
}

void driver_set_evict_file(options_t* ops, const char* fn) {
  strncpy(ops->evict_file, fn, FILENAME_MAX);
}

void driver_log_keys(void* op, const char* line) {
  options_t* ops = (options_t*)op;
  fprintf(ops->output_file_ptr, "%s\n", line);
}

void driver_log_evicted_keys(void* op, int k) {
  options_t* ops = (options_t*)op;
  if (k == INT_MIN) {
    fprintf(ops->evict_file_ptr, "\n");
  } else {
    fprintf(ops->evict_file_ptr, "%i\n", k);
  }
}

void driver_close(options_t* ops) {
  fclose(ops->input_file_ptr);
  fclose(ops->output_file_ptr);
  fclose(ops->evict_file_ptr);
  free(ops);
}

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

static bool is_next(options_t* ops) {
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

void driver_init(options_t** ops, int argc, char** argv, const char* of, const char* ef) {
  if (argc != 3) {
    perror("Relaunch with args [size of lru] inputfile");
    exit(EXIT_FAILURE);
  }

  *ops = calloc(1, sizeof(options_t));

  options_t* op = *ops;
  op->lru_size = atoi(argv[1]);
  strncpy(op->input_file, argv[2], FILENAME_MAX);
  strncpy(op->output_file, of, FILENAME_MAX);
  strncpy(op->evict_file, ef, FILENAME_MAX);

  op->input_file_ptr = fopen(op->input_file, "r");
  op->output_file_ptr = fopen(op->output_file, "w");
  op->evict_file_ptr = fopen(op->evict_file, "w");
}

int32_t driver_next_input(options_t* ops) { 
  if (!is_next(ops))
    return -1;

  int32_t size;
  fscanf(ops->input_file_ptr, "%i\n" , &size);
  return size;
}

int32_t driver_next_input_extended(options_t* ops, bool* is_resize) { 
  if (!is_next(ops))
    return -1;

  *is_resize = false;

  char next_char = fgetc(ops->input_file_ptr);
  if (next_char == 'R') {
   *is_resize = true;
   next_char = fgetc(ops->input_file_ptr);

  } else {
    ungetc(next_char, ops->input_file_ptr);
  }

  int32_t size = 0;  
  fscanf(ops->input_file_ptr, "%i\n" , &size);

  return size;
}

int driver_lru_size(options_t* ops) { 
  return ops->lru_size;
}

FILE* driver_get_output_fd(options_t* ops) { 
  return ops->output_file_ptr;
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

#include "driver.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void driver_init(options_t* ops, int argc, char** argv) {
  if (argc != 3) {
    perror("Relaunch with args [size of lru] inputfile");
    exit(EXIT_FAILURE);
  }

  ops->lru_size = atoi(argv[1]);
  strncpy(ops->input_file, argv[2], FILENAME_SIZE);

  ops->input_file_ptr = fopen(ops->input_file, "r");
  ops->output_file_ptr = fopen(ops->output_file, "w");
  ops->evict_file_ptr = fopen(ops->evict_file, "w");
}

bool is_next(options_t* ops) {
  return !feof(ops->input_file_ptr);
}

int next_input(options_t* ops) { 
  char input[16] = {0};
  fgets(input, 16, ops->input_file_ptr);
  if (input[0] == '\0') 
    exit(EXIT_FAILURE);
  return atoi(input);
}

int get_lru_size(options_t* ops) { 
  return ops->lru_size;
}

void print_lru_keys_to_file(options_t* ops, const char* line) {
  fprintf(ops->output_file_ptr, "%s\n", line);
}

void print_lru_evicted_to_file(options_t* ops, int k) {
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
}

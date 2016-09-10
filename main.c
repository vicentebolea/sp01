#include <string.h>
#include <stdlib.h>

#include "lru.h"
#include "driver.h"

int main(int argc, char *argv[])
{
  options_t ops;
  lru_t* lru = NULL;

  strcpy(ops.output_file, "list.txt");
  strcpy(ops.evict_file, "evict.txt");
  driver_init(&ops, argc, argv);
  lru_init(&lru, ops.lru_size);

  char* keys = malloc(sizeof(char)*LRU_PRINT_STRING);
  while (is_next(&ops)) {
    int input = next_input(&ops);
    int evicted_key = lru_insert(lru, input);
    lru_print(lru, &keys);
    print_lru_evicted_to_file(&ops, evicted_key);
    print_lru_keys_to_file(&ops, keys);
  }
  free(keys);

  driver_close(&ops);
  lru_destroy(lru);
  
  return EXIT_SUCCESS;
}

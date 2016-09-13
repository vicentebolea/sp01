#include "lru.h"
#include "driver.h"

#include <stdlib.h>

int main(int argc, char *argv[]) {
  options_t* ops = NULL;
  lru_t* lru = NULL;

  driver_init(&ops, argc, argv, "list.txt", "evict.txt");
  lru_init(&lru, driver_lru_size(ops));

  int32_t input;
  while (-1 != (input = driver_next_input(ops))) {
    int evicted_key = lru_insert(lru, input);
    lru_visitor(lru, driver_get_output_fd(ops));
    driver_log_evicted_keys(ops, evicted_key);
  }

  driver_destroy(ops);
  lru_destroy(lru);
  
  return EXIT_SUCCESS;
}

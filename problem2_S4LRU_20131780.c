#include "s4lru.h"
#include "driver.h"

#include <stdlib.h>

int main(int argc, char *argv[]) {
  options_t* ops = NULL;
  s4lru_t* lru = NULL;

  driver_init(&ops, argc, argv, "list.txt", "evict.txt");
  s4lru_init(&lru, driver_lru_size(ops));

  int32_t input;
  while (-1 != (input = driver_next_input(ops))) {
    int evicted_key = s4lru_insert(lru, input);
    s4lru_visitor(lru);
    driver_log_evicted_keys(ops, evicted_key);
  }

  driver_destroy(ops);
  s4lru_destroy(lru);
  
  return EXIT_SUCCESS;
}

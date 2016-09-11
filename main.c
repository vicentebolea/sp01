#include <stdlib.h>

#include "lru.h"
#include "driver.h"

int main(int argc, char *argv[])
{
  options_t* ops = NULL;
  lru_t* lru = NULL;

  driver_init(&ops, argc, argv, "list.txt", "evict.txt");
  lru_init(&lru, driver_lru_size(ops));

  while (is_next(ops)) {
    int input = next_input(ops);
    int evicted_key = lru_insert(lru, input);
    lru_visitor(lru, &driver_log_keys, ops);
    driver_log_evicted_keys(ops, evicted_key);
  }

  driver_close(ops);
  lru_destroy(lru);
  
  return EXIT_SUCCESS;
}

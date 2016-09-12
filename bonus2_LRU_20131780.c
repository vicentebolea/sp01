#include "s4lru.h"
#include "driver.h"

#include <stdlib.h>

int main(int argc, char *argv[]) {
  options_t* ops = NULL;
  s4lru_t* lru = NULL;

  driver_init(&ops, argc, argv, "list.txt", "evict.txt");
  s4lru_init(&lru, driver_lru_size(ops));


  int32_t input;
  bool is_resize = false;
  while (-1 != (input = driver_next_input_extended(ops, &is_resize))) {
    if (is_resize) {
      s4lru_resize(lru, input);

    } else {
      int evicted_key = s4lru_insert(lru, input);
      driver_log_evicted_keys(ops, evicted_key);
    }
    s4lru_visitor(lru);
  }

  driver_close(ops);
  s4lru_destroy(lru);

  return EXIT_SUCCESS;
}

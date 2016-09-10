#include <string.h>
#include <stdlib.h>

#include "lru.h"
#include "driver.h"

int main(int argc, char *argv[])
{
  options_t ops;
  strcpy(ops.output_file, "list.txt");
  lru_t lru;

  parse_args(argc, argv, &ops);
  load_file(ops.input_file);
  lru_init(&lru, ops.lru_size);

  while (is_next(&ops)) {
    char output[LRU_PRINT_STRING];
    int input = next_input(&ops);
    lru_insert(&lru, input);
    lru_print(&lru, output);
    save_output(output);
  }

  
  return EXIT_SUCCESS;
}

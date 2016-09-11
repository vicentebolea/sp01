#pragma once
#include <stdbool.h>

struct options_t;
typedef struct options_t options_t;

void driver_init(options_t**, int, char**, const char*, const char*);
int  driver_lru_size(options_t*);
void driver_set_output_file(options_t*, const char*);
void driver_set_evict_file(options_t*, const char*);
void driver_log_keys(void*, const char*);
void driver_log_evicted_keys(void*, int);
void driver_close(options_t*);

bool is_next(options_t*);
int next_input(options_t*);

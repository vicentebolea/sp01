#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

struct options_t;
typedef struct options_t options_t;

void driver_init(options_t**, int, char**, const char*, const char*);
int  driver_lru_size(options_t*);
void driver_log_keys(void*, const char*);
void driver_log_evicted_keys(void*, int);
void driver_close(options_t*);
int32_t driver_next_input(options_t*);
int32_t driver_next_input_extended(options_t* ops, bool*);
FILE* driver_get_output_fd(options_t* ops);

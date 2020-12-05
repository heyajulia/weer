#pragma once

#include <stdbool.h>
#include <stddef.h>

struct char_buf_t {
  char* data;
  size_t size;
};

struct char_buf_t* char_buf_init();
bool char_buf_append(struct char_buf_t* cb, char* data, size_t data_size);
char* char_buf_to_string(struct char_buf_t* cb);
void char_buf_deinit(struct char_buf_t* cb);

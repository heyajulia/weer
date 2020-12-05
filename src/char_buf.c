#include "char_buf.h"

#include <stdlib.h>
#include <string.h>

struct char_buf_t* char_buf_init() {
  struct char_buf_t* cb = malloc(sizeof(struct char_buf_t));
  cb->data = NULL;
  cb->size = 0;

  return cb;
}

bool char_buf_append(struct char_buf_t* cb, char* data, size_t data_size) {
  char* tmp = realloc(cb->data, cb->size + data_size);

  if (tmp == NULL) {
    return false;
  }

  cb->data = tmp;

  memcpy(cb->data + cb->size, data, data_size);
  cb->size += data_size;

  return true;
}

char* char_buf_to_string(struct char_buf_t* cb) {
  char* buf = malloc(cb->size + 1);
  memcpy(buf, cb->data, cb->size);
  buf[cb->size] = '\0';

  return buf;
}

void char_buf_deinit(struct char_buf_t* cb) {
  free(cb->data);
  free(cb);
}

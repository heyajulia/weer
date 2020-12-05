#include "weer.h"
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include "char_buf.h"

size_t write_data(void* buffer,
                  __attribute__((unused)) size_t size,
                  size_t nmemb,
                  void* userp) {
  struct char_buf_t* cb = (struct char_buf_t*)userp;

  if (!char_buf_append(cb, (char*)buffer, nmemb)) {
    return 0;
  }

  return nmemb;
}

char* http_get(CURL* handle, const char* url, CURLcode* code) {
  struct char_buf_t* cb = char_buf_init();

  curl_easy_setopt(handle, CURLOPT_URL, url);

  if (strstr(url, "ipinfo.io")) {
    curl_easy_setopt(handle, CURLOPT_USERAGENT, WEER_IPINFO_USER_AGENT);
  } else {
    curl_easy_setopt(handle, CURLOPT_USERAGENT, WEER_API_USER_AGENT);
  }

  curl_easy_setopt(handle, CURLOPT_WRITEDATA, cb);
  curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);

  if ((*code = curl_easy_perform(handle)) != CURLE_OK) {
    char_buf_deinit(cb);

    return NULL;
  }

  char* buf = char_buf_to_string(cb);

  char_buf_deinit(cb);

  return buf;
}

double* parse_coordinates(char* s) {
  double* coordinates = malloc(2 * sizeof(double));
  char* next;

  coordinates[0] = strtod(s, &next);
  // next + 1 because next now points to the the ','.
  coordinates[1] = strtod(next + 1, NULL);

  return coordinates;
}

int main(__attribute__((unused)) int argc,
         __attribute__((unused)) const char* argv[]) {
  curl_global_init(CURL_GLOBAL_ALL);

  CURL* h = curl_easy_init();
  CURLcode code;

  char* buf = http_get(h, "https://ipinfo.io/loc", &code);

  if (buf == NULL) {
    fprintf(stderr, "cURL error: %s\n", curl_easy_strerror(code));

    curl_easy_cleanup(h);
    curl_global_cleanup();

    exit(1);
  }

  double* coordinates = parse_coordinates(buf);
  free(buf);

  char url[256];

  if (sprintf(url, WEER_API_URL, coordinates[0], coordinates[1]) < 0) {
    perror("snprintf");
    exit(1);
  }

  buf = http_get(h, url, &code);

  printf("%s\n", buf);
  free(buf);

  printf("\n%s\n", WEER_API_CREDIT);

  free(coordinates);

  curl_easy_cleanup(h);
  curl_global_cleanup();
}

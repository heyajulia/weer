#include <curl/curl.h>
#include <string.h>
#include "char_buf.h"
#include "weer.h"

static size_t write_data(void* buffer,
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

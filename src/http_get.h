#pragma once

#include <curl/curl.h>

char* http_get(CURL* handle, const char* url, CURLcode* code);

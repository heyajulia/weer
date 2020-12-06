#pragma once

#include <curl/curl.h>

#define WEER_VERSION "0.1.2"
#define WEER_REPOSITORY_URL "https://github.com/heyajulia/weer"
#define WEER_IPINFO_USER_AGENT "curl/" LIBCURL_VERSION
#define WEER_API_USER_AGENT "weer/" WEER_VERSION " (+" WEER_REPOSITORY_URL ")"
#define WEER_API_URL                                    \
  "https://api.met.no/weatherapi/locationforecast/2.0/" \
  "compact?lat=%.4f&lon=%.4f"
#define WEER_API_CREDIT                                                  \
  "Weather forecast from Yr, delivered by the Norwegian Meteorological " \
  "Institute and NRK"

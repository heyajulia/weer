#include "weer.h"
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include "http_get.h"
#include "parse_coordinates.h"

int main(int argc, const char* argv[]) {
  // HACK: make weer --version work for Bintray
  if (argc == 2 && strcmp(argv[1], "--version") == 0) {
    fprintf(stderr, "%s\n", WEER_VERSION);
    exit(EX_USAGE);
  }

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

  free(coordinates);

  buf = http_get(h, url, &code);

  printf("%s\n", buf);
  free(buf);

  printf("\n%s\n", WEER_API_CREDIT);

  curl_easy_cleanup(h);
  curl_global_cleanup();
}

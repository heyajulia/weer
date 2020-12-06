#include <stddef.h>
#include <stdlib.h>

double* parse_coordinates(char* s) {
  double* coordinates = malloc(2 * sizeof(double));
  char* next;

  coordinates[0] = strtod(s, &next);
  // next + 1 because next now points to the the ','.
  coordinates[1] = strtod(next + 1, NULL);

  return coordinates;
}

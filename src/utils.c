#include <stdlib.h>
#include <errno.h>

#include "utils.h"

// insertion sort
void arr_sort(int arr[], int size)
{
  int i, key, j;
  for (i = 1; i < size; i++) {
    key = arr[i];
    j = i - 1;
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j = j - 1;
    }
    arr[j + 1] = key;
  }
}

long file_size(FILE *fd)
{
  fseek(fd, 0L, SEEK_END);
  long fsize = ftell(fd);
  fseek(fd, 0L, SEEK_SET);
  return fsize;
}

int file_copy(FILE *fd, char *fn)
{
  if (fn == NULL || strncmp(fn, "", 1) == 0) {
    fprintf(stderr, "ERROR: `in_file` is empty.\n");
    exit(-2);
  }
  char *cpfn = (char*)malloc(strlen(fn) + strlen(extension) + 1);
  cpfn = strndup(fn, strlen(fn));
  strncat(cpfn, extension, strlen(extension)+1);

  FILE *copyfd = fopen(cpfn, "w+");
  if (copyfd == NULL) {
    perror("ERROR: [file_copy]> `fopen()`");
    exit(-2);
  }

  char c = fgetc(fd);
  while (c != EOF) {
    fputc(c, copyfd);
    c = fgetc(fd);
  }

  fclose(copyfd);
  free(cpfn);
  return 1;
}

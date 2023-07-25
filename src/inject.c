#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>
#include <locale.h>
#include <errno.h>

#include "utils.h"


void zwsp_inject(FILE *fd, char *fn, int mode)
{
  setlocale(LC_CTYPE, "");
  wchar_t zwsp_byte = 0x200b;

  char *cpfn = (char*)malloc(strlen(fn) + 4);
  cpfn = strndup(fn, strlen(fn));
  strncat(cpfn, ".cp", 4);

  FILE *copyfd = fopen(cpfn, "w+");
  if (copyfd == NULL) {
    perror("ERROR: [zwsp_inject]> `fopen()`");
    exit(-2);
  }

  int stream = fwide(copyfd, 1); //set to wide-character oriented stream
  if (stream < 0) {
    fprintf(stderr, "ERROR: file '%s' is byte oriented.\n", fn);
    exit(-2);
  }

  long fsize = file_size(fd);

  if (mode == LIGHT) {
    srand(time(NULL));
    int randarr[3];
    for (size_t i = 0; i<ARRAY_SIZE(randarr); ++i) {
      randarr[i] = rand() % fsize;
    }
    arr_sort(randarr, ARRAY_SIZE(randarr));
    printf("randarr[0] = %d\n", randarr[0]);
    printf("randarr[1] = %d\n", randarr[1]);
    printf("randarr[2] = %d\n", randarr[2]);
    int i = 0;
    char c = fgetc(fd);
    while (c != EOF) {
      fwprintf(copyfd, L"%lc", c);
      if (ftell(fd) == randarr[i]) {
	fwprintf(copyfd, L"%lc", zwsp_byte);
	++i;
      }
      c = fgetc(fd);
    }
  } else {
    char c = fgetc(fd);
    while (c != EOF) {
      fwprintf(copyfd, L"%lc", c);
      fwprintf(copyfd, L"%lc", zwsp_byte);
      c = fgetc(fd);
    }
  } 

  fclose(copyfd);
  fclose(fd);

  int rn = rename(cpfn, fn);
  if (rn == -1) {
    perror("ERROR: [zwsp_inject]> `rename()`");
    exit(-2);
  }
  free(cpfn);
}

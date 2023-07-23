#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <wchar.h>
#include <locale.h>

#include "argparse.h"


char *infile;
int MAKE_COPY = 0;
static const char extension[6] = ".cbcp"; /* copied files extension */

static const char doc[] =
  "\nCode Breaker -- a program to inject files with ZWSP \"zero-width space\"";

static const char *usages[] = {
    "code-breaker -f in_file [options]",
    NULL,
};

static struct argparse_option options[] = {
  OPT_HELP(),
  OPT_GROUP("General options"),
  OPT_STRING('f',  "file", &infile,    "File to inject",                                        NULL, 0, 0),
  OPT_BOOLEAN('c', "copy", &MAKE_COPY, "Make a copy of the original file. (extension:'.cbcp')", NULL, 0, 0),
  OPT_END(),
};

int copy_file(FILE *origfd, char *fn);
void zwsp_inject(FILE *fd, char *fn);

int main(int argc, const char *argv[])
{
  struct argparse argparse;

  argparse_init(&argparse, options, usages, 0);
  if (argc < 2) {
    argparse_usage(&argparse);
    exit(-1);
  }

  argparse_describe(&argparse, doc, NULL);
  argc = argparse_parse(&argparse, argc, argv);

  FILE *fd = fopen(infile, "r");
  if (fd == NULL) {
    perror("ERROR: [main]> `fopen()`");
    exit(-2);
  }

  if (MAKE_COPY) {
    copy_file(fd, infile);
    rewind(fd);
  }

  zwsp_inject(fd, infile);
  /* `fd` will be closed in the `zwsp_inject()` function */
  return 0;
}

int copy_file(FILE *origfd, char *fn)
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
    perror("ERROR: [copy_file]> `fopen()`");
    /* DEV: should i `free(cpfn)` here ? */
    exit(-2);
  }

  char c = fgetc(origfd);
  while (c != EOF) {
    fputc(c, copyfd);
    c = fgetc(origfd);
  }

  fclose(copyfd);
  free(cpfn);
  return 1;
}

void zwsp_inject(FILE *fd, char *fn)
{
  setlocale(LC_CTYPE, "");
  wchar_t zwsp_byte = 0x200b;

  char *cpfn = (char*)malloc(strlen(fn) + 4);
  cpfn = strndup(fn, strlen(fn));
  strncat(cpfn, ".cp", 4);

  FILE *copyfd = fopen(cpfn, "w+");
  if (copyfd == NULL) {
    perror("ERROR: [zwsp_inject]> `fopen()`");
    /* DEV: should i `free(cpfn)` here ? */
    exit(-2);
  }

  int stream = fwide(copyfd, 1); //set to wide-character oriented stream, see manual `$ man fwide`
  if (stream < 0) {
    fprintf(stderr, "ERROR: file '%s' is byte oriented.\n", fn);
    /* DEV: should i `free(cpfn)` here ? */
    exit(-2);
  }

  char c = fgetc(fd);
  while (c != EOF) {
    fwprintf(copyfd, L"%lc", c);
    fwprintf(copyfd, L"%lc", zwsp_byte);
    c = fgetc(fd);
  }

  fclose(copyfd);
  fclose(fd);

  int rn = rename(cpfn, fn); //rename() will remove the file named `fn`, see manual `https://www.gnu.org/software/libc/manual/html_node/Renaming-Files.html`
  if (rn == -1) {
    perror("ERROR: [zwsp_inject]> `rename()`");
    // DEV: should i `free(cpfn)` here ? /
    exit(-2);
  }
  free(cpfn);
}

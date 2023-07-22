#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

#include "argparse.h"


char *infile;
int MAKE_COPY = 0;
static const char extension[6] = ".cbcp"; /* copied files extension */

static char doc[] =
  "\nCode Breaker -- a program to inject files with ZWSP \"zero-width space\"";

static const char *usages[] = {
    "code-breaker -f infile [options]",
    NULL,
};

int copy_file(FILE *origfd, char *fn);
void zwsp_inject(FILE *fd, char *fn);

int main(int argc, const char *argv[])
{
  struct argparse argparse;
  struct argparse_option options[] = {
    OPT_HELP(),
    OPT_GROUP("General options"),
    OPT_STRING('f',  "file", &infile,    "File to inject",                                        NULL, 0, 0),
    OPT_BOOLEAN('c', "copy", &MAKE_COPY, "Make a copy of the original file. (extension:'.cbcp')", NULL, 0, 0),
    OPT_END(),
  };

  argparse_init(&argparse, options, usages, 0);
  if (argc < 2) {
    argparse_usage(&argparse);
    exit(-1);
  }
  argparse_describe(&argparse, doc, NULL);
  argc = argparse_parse(&argparse, argc, argv);

  FILE *fd = fopen(infile, "r");
  if (MAKE_COPY) {
    copy_file(fd, infile);
  }

  zwsp_inject(fd, infile);
  return 0;
}

int copy_file(FILE *origfd, char *fn)
{
  char *cpfn;
  cpfn = strndup(fn, strlen(fn));
  strncat(cpfn, extension, strlen(extension)+1);
  FILE *copyfd = fopen(cpfn, "w+");

  char c = fgetc(origfd);
  while (c != EOF) {
    fputc(c, copyfd);
    c = fgetc(origfd);
  }

  fclose(copyfd);
  return 1;
}

void zwsp_inject(FILE *fd, char *fn)
{
  setlocale(LC_CTYPE, "");
  wchar_t zwsp_byte = 0x200b;

  char *cpfn;
  cpfn = strndup(fn, strlen(fn));
  strncat(cpfn, ".cp", 4);
  FILE *copyfd = fopen(cpfn, "w+");

  int stream = fwide(copyfd, 1); //wide-character oriented stream
  if (stream < 0) {
    fprintf(stderr, "ERROR: file '%s' is byte oriented.\n", fn);
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
  rename(cpfn, fn); //rename() will remove the file named `fn`
}

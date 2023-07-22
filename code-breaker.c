#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

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

int make_file_copy(FILE *origfd, char *filename);

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

  FILE *fd = fopen(infile, "a+");
  if (MAKE_COPY) {
    make_file_copy(fd, infile);
  }

  return 0;
}

int make_file_copy(FILE *origfd, char *filename)
{
  char *cpfilename;
  cpfilename = strndup(filename, strlen(filename));
  strncat(cpfilename, extension, strlen(extension)+1);
  FILE *copyfd = fopen(cpfilename, "w+");

  char c = fgetc(origfd);
  while (c != EOF) {
    fputc(c, copyfd);
    c = fgetc(origfd);
  }
  fclose(copyfd);
  return 1;
}

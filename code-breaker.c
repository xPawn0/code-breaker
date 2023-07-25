#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <wchar.h>
#include <locale.h>

#include "argparse.h"
#include "utils.h"

char *infile;
int MAKE_COPY = 0;
int mode = HEAVY;

static const char doc[] =
  "\nCode Breaker -- a program to inject files with ZWSP \"zero-width space\"";

static const char *usages[] = {
    "code-breaker -f in_file [options]",
    NULL,
};

static struct argparse_option options[] = {
  OPT_HELP(),
  OPT_GROUP("General options"),
  OPT_STRING('f',  "file",  &infile,    "File to inject.",                   NULL, 0,     0),
  OPT_BOOLEAN('c', "copy",  &MAKE_COPY, "Make a copy of the original file.", NULL, 0,     0),
  OPT_INTEGER('m', "mode", &mode,      "Set injection mode. (light=0, default: heavy=1)",                NULL, LIGHT, 0),
  OPT_END(),
};

void zwsp_inject(FILE *fd, char *fn, int mode);

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
    file_copy(fd, infile);
    rewind(fd);
  }

  printf("mode: \"%d\"\n", mode);
  zwsp_inject(fd, infile, mode);
  return 0;
}

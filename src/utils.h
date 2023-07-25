#pragma once

#include <stdio.h>
#include <string.h>
#include "argparse.h"

#define ARRAY_SIZE(arr) sizeof(arr)/sizeof(arr[0])

#define VERSION "v2.1"
#define LIGHT 0
#define HEAVY 1

static const char extension[6] = ".cbcp";

void arr_sort(int arr[], int size);

long file_size(FILE *fd);
int file_copy(FILE *fd, char *fn);

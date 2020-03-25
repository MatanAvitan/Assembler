#ifndef FINAL_PROJECT_UTILS_H
#define FINAL_PROJECT_UTILS_H

#include "consts.h"
#include <stdlib.h>
#include <string.h>


int dec_to_binary(int n, int bits_count, char *out_buffer);

int starts_with(const char *pre, const char *str);

char *int_to_string(int num, char *num_as_string);

#endif /*FINAL_PROJECT_UTILS_H*/
#ifndef CUBE3D_H
#define CUBE3D_H

#include "libft.h"

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// UTILS
void putstr_error_and_exit(char *error, int exit_code);

// VALIDATIONS
int is_cub(char *src_map);

#endif

#ifndef CUBE3D_H
#define CUBE3D_H

#include "libft.h"
#include "get_next_line.h"

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// UTILS
void perror_and_exit(char *error, int exit_code);

// VALIDATIONS
int is_cub(char *src_map);

#endif

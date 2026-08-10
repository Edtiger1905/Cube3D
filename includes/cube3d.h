#ifndef CUBE3D_H
#define CUBE3D_H

#include "mlx.h"
#include "libft.h"
#include "get_next_line.h"

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_cube3d
{
    int fd;
} t_cube3d;

// UTILS
void perror_and_exit(char *error, int exit_code);

// VALIDATOR
int validate_argv_and_return_fd(int argc, char **argv);

#endif

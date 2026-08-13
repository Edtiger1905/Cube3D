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
    void *mlx_ptr;
} t_cube3d;

// free_memory.c
void free_cube3d(t_cube3d *cube3d);

// init_cube3d.c
t_cube3d init_cube3d(int argc, char **argv);

// utils.c
void perror_and_exit(t_cube3d *cube3d, char *msg_error, int exit_code);

// validator.c
int validate_and_return_fd(int argc, char **argv);

#endif
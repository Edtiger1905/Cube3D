#ifndef CUBE3D_H
#define CUBE3D_H

#include "mlx.h"
#include "libft.h"
#include "get_next_line.h"

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_textures
{
    void *north;
    void *south;
    void *east;
    void *west;
    int floor;
    int ceiling;
} t_textures;

typedef struct s_cube3d
{
    int fd;
    void *mlx_ptr;
    int width;
    int height;
    t_textures textures;
} t_cube3d;

// free_memory.c
void free_cube3d(t_cube3d *cube3d);

// init_cube3d.c
t_cube3d init_cube3d(int argc, char **argv);

// init_textures.c
void init_textures(t_cube3d *cube3d);

// parser_rgb_texture.c
void parser_rgb_texture(t_cube3d *cube3d, char **line);

// parser_texture.c
void parser_texture(t_cube3d *cube3d, char **line);

// parser_utils.c
int matrix_length(char **matrix);
void free_matrix(char **matrix);
void flush_gnl(int fd);
void free_matrix_and_flush_gnl(t_cube3d *cube3d, char **matrix);

// utils.c
void perror_and_exit(t_cube3d *cube3d, char *msg_error, int exit_code);

// validator.c
int validate_and_return_fd(int argc, char **argv);

#endif
#ifndef CUBE3D_H
#define CUBE3D_H

#include "mlx.h"
#include "libft.h"
#include "get_next_line.h"

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_map
{
    int lines;

    char **matrix;
} t_map;

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
    int argc;
    char **argv;

    int fd;
    char *src_map;

    void *mlx_ptr;

    t_textures textures;

    t_map map;
} t_cube3d;

// free_memory.c
void free_cube3d(t_cube3d *cube3d);
void free_matrix(char **matrix);

// init_cube3d.c
void init_cube3d(t_cube3d *cube3d);

// parser_map.c
void parser_map(t_cube3d *cube3d);

// parser_rgb_utils.c
char **parser_rgb_initialize_matrix(t_cube3d *cube3d, char *line);

// parser_rgb.c
void parser_rgb(t_cube3d *cube3d, char *line);

// parser_texture.c
void parser_texture(t_cube3d *cube3d, char *line);

// parser_textures.c
void parser_textures(t_cube3d *cube3d);

// utils.c
void perror_and_exit(t_cube3d *cube3d, char *msg_error);
int is_cub_extension(char *src_map);
void open_file_and_setconfig(t_cube3d *cube3d);
int matrix_length(char **matrix);
int is_map(char *line);

#endif
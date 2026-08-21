#include "cube3d.h"

static void flush_gnl(t_cube3d *cube3d)
{
    char *line;

    if (cube3d->fd >= 0)
    {
        while ((line = get_next_line(cube3d->fd)))
            free(line);
        close(cube3d->fd);
    }
}

void free_cube3d(t_cube3d *cube3d)
{
    flush_gnl(cube3d);

    if (cube3d->mlx_ptr)
    {
        if (cube3d->textures.north)
            mlx_destroy_image(cube3d->mlx_ptr, cube3d->textures.north);
        if (cube3d->textures.south)
            mlx_destroy_image(cube3d->mlx_ptr, cube3d->textures.south);
        if (cube3d->textures.east)
            mlx_destroy_image(cube3d->mlx_ptr, cube3d->textures.east);
        if (cube3d->textures.west)
            mlx_destroy_image(cube3d->mlx_ptr, cube3d->textures.west);
        mlx_destroy_display(cube3d->mlx_ptr);
        free(cube3d->mlx_ptr);
    }
}

void free_matrix(char **matrix)
{
    int i;

    if (!matrix)
        return;
    i = 0;
    while (matrix[i])
    {
        free(matrix[i]);
        i++;
    }
    free(matrix);
}
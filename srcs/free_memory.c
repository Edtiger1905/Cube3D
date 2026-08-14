#include "cube3d.h"

void free_cube3d(t_cube3d *cube3d)
{
    if (cube3d->textures.north)
        mlx_destroy_image(cube3d->mlx_ptr, cube3d->textures.north);
    if (cube3d->textures.south)
        mlx_destroy_image(cube3d->mlx_ptr, cube3d->textures.south);
    if (cube3d->textures.east)
        mlx_destroy_image(cube3d->mlx_ptr, cube3d->textures.east);
    if (cube3d->textures.west)
        mlx_destroy_image(cube3d->mlx_ptr, cube3d->textures.west);
    if (cube3d->mlx_ptr)
        (mlx_destroy_display(cube3d->mlx_ptr), free(cube3d->mlx_ptr));
}
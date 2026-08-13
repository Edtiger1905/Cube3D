#include "cube3d.h"

void free_cube3d(t_cube3d *cube3d)
{
    if (cube3d->mlx_ptr)
        (mlx_destroy_display(cube3d->mlx_ptr), free(cube3d->mlx_ptr));
}
#include "cube3d.h"

void init_cube3d(t_cube3d *cube3d)
{
    cube3d->mlx_ptr = mlx_init();
    if (!cube3d->mlx_ptr)
        return perror_and_exit(cube3d, "MiniLibX error: Failed to initialize MLX");
    parser_textures(cube3d);
}
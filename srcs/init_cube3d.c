#include "cube3d.h"

void init_cube3d(t_cube3d *cube3d)
{
    cube3d->mlx_ptr = mlx_init();
    if (!cube3d->mlx_ptr)
        return perror_and_exit(cube3d, "[INIT CUBE3D] Failed to initialize MLX");
    cube3d->fd = -1;
    cube3d->textures.north = NULL;
    cube3d->textures.south = NULL;
    cube3d->textures.east = NULL;
    cube3d->textures.west = NULL;
    cube3d->textures.floor = -1;
    cube3d->textures.ceiling = -1;
    cube3d->map.lines = 0;
    cube3d->map.matrix = NULL;
    parser_textures(cube3d);
    parser_map(cube3d);
}
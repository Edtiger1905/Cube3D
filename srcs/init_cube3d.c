#include "cube3d.h"

t_cube3d init_cube3d(int argc, char **argv)
{
    t_cube3d cube3d;

    cube3d.fd = validate_and_return_fd(argc, argv);
    cube3d.mlx_ptr = mlx_init();
    if (!cube3d.mlx_ptr)
        perror_and_exit(NULL, "[INIT CUBE3D] mlx init error", 1);
    return (cube3d);
}
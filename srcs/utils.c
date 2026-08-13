#include "cube3d.h"

void perror_and_exit(t_cube3d *cube3d, char *msg_error, int exit_code)
{
    ft_putstr_fd("Error:\n", 1);
    ft_putstr_fd(msg_error, 1);
    ft_putchar_fd('\n', 1);
    if (cube3d)
        free_cube3d(cube3d);
    exit(exit_code);
}

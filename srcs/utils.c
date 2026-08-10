#include "cube3d.h"

void perror_and_exit(char *error, int exit_code)
{
    ft_putstr_fd("Error:\n", 1);
    ft_putstr_fd(error, 1);
    ft_putchar_fd('\n', 1);

    exit(exit_code);
}

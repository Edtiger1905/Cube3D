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

int matrix_length(char **matrix)
{
    int i;

    i = 0;
    if (!matrix)
        return (i);
    while (matrix[i])
        i++;
    return (i);
}

int is_map(char *line)
{
    int i;

    if (!line || line[0] == '\0')
        return (0);
    i = 0;
    while (line[i])
    {
        if (line[i] != ' ' && line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
            return (0);
        i++;
    }
    return (1);
}
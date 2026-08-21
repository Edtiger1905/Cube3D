#include "cube3d.h"

void perror_and_exit(t_cube3d *cube3d, char *msg_error)
{
    ft_putstr_fd("Error:\n", 1);
    ft_putstr_fd(msg_error, 1);
    ft_putchar_fd('\n', 1);
    if (cube3d)
        free_cube3d(cube3d);
    exit(1);
}

int is_cub_extension(char *src_map)
{
    char *s;

    s = ft_strrchr(src_map, '.');

    if (!s || ft_strlen(s) > 4 || ft_strncmp(s, ".cub", 4) != 0)
        return (0);

    return (1);
}

void open_file_and_setconfig(t_cube3d *cube3d)
{
    int fd;
    char *src_map;

    if (cube3d->argc < 2)
        return (perror_and_exit(cube3d, "[ARGUMENTS VALIDATOR UTILS] Please provide a map file"));
    if (cube3d->argc > 2)
        return (perror_and_exit(cube3d, "[ARGUMENTS VALIDATOR UTILS] Only one map file is allowed"));
    src_map = cube3d->argv[1];
    if (!is_cub_extension(src_map))
        return (perror_and_exit(cube3d, "[FILE VALIDATOR UTILS] Map must end with '.cub'"));
    fd = open(src_map, O_RDONLY);
    if (fd < 0)
        return (perror_and_exit(cube3d, "[FILE VALIDATOR UTILS] Cannot open the map file"));
    cube3d->fd = fd;
    cube3d->src_map = src_map;
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
        if (line[i] != ' ' && line[i] != '0' && line[i] != '1' &&
            line[i] != 'N' && line[i] != 'S' && line[i] != 'E' &&
            line[i] != 'W')
            return (0);
        i++;
    }
    return (1);
}
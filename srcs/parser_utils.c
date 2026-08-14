#include "cube3d.h"

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

void free_matrix(char **matrix)
{
    int i;
    int len;

    i = 0;
    len = matrix_length(matrix);
    while (i < len)
    {
        free(matrix[i]);
        i++;
    }
    free(matrix);
}

void flush_gnl(int fd)
{
    char *line;

    if (fd >= 0)
    {
        while ((line = get_next_line(fd)))
            free(line);
        close(fd);
    }
}

void free_matrix_and_flush_gnl(t_cube3d *cube3d, char **matrix)
{
    free_matrix(matrix);
    flush_gnl(cube3d->fd);
}
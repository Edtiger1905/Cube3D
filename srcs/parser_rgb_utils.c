#include "cube3d.h"

static void free_helper(char *tmp, char *line)
{
    if (tmp)
        free(tmp);
    if (line)
        free(line);
}

static int is_valid_str_rgb(char *str_rgb)
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(str_rgb);
    while (i < len)
    {
        if (!(ft_isdigit(str_rgb[i]) || str_rgb[i] == ','))
            return (0);
        i++;
    }
    return (1);
}

char **parser_rgb_initialize_matrix(t_cube3d *cube3d, char *line)
{
    char *tmp;
    char **matrix;

    tmp = ft_strtrim(line, "\n");
    matrix = ft_split(tmp, ' ');
    free_helper(tmp, line);
    if (matrix_length(matrix) != 2)
    {
        free_matrix(matrix);
        perror_and_exit(cube3d, "[PARSER RGB UTILS] Expected '<F/C> <R,G,B>'");
    }
    if (!is_valid_str_rgb(matrix[1]))
    {
        free_matrix(matrix);
        perror_and_exit(cube3d, "[PARSER RGB UTILS] Only digits and commas are allowed on RGB characters");
    }
    return (matrix);
}
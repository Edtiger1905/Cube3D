#include "cube3d.h"

typedef struct s_context
{
    int *rgb;
    char **matrix;
    char **rgb_matrix;
    t_cube3d *cube3d;
} t_context;

static void free_parser_rgb(t_context context)
{
    if (context.rgb)
        free(context.rgb);
    if (context.matrix)
        free_matrix(context.matrix);
    if (context.rgb_matrix)
        free_matrix(context.rgb_matrix);
}

static void rgb_atoi(t_context context)
{
    int i;
    int rgb_matrix_len;

    i = 0;
    rgb_matrix_len = matrix_length(context.rgb_matrix);
    while (i < rgb_matrix_len)
    {
        context.rgb[i] = ft_atoi(context.rgb_matrix[i]);
        i++;
    }
}

static void set_rgb(t_cube3d *cube3d, t_context context)
{
    int R;
    int G;
    int B;
    int rgb_color;

    R = context.rgb[0];
    G = context.rgb[1];
    B = context.rgb[2];
    rgb_color = (R << 16) | (G << 8) | B;
    if (ft_strncmp(context.matrix[0], "F", 1) == 0)
    {
        if (cube3d->textures.floor != -1)
            return (free_parser_rgb(context), perror_and_exit(cube3d, "Duplicate RGB configuration: Floor color is already set", 1));
        cube3d->textures.floor = rgb_color;
    }
    else if (ft_strncmp(context.matrix[0], "C", 1) == 0)
    {
        if (cube3d->textures.ceiling != -1)
            return (free_parser_rgb(context), perror_and_exit(cube3d, "Duplicate RGB configuration: Ceiling color is already set", 1));
        cube3d->textures.ceiling = rgb_color;
    }
}

void parser_rgb(t_cube3d *cube3d, char **tmp)
{
    t_context context;

    context.rgb = NULL;
    context.matrix = ft_split(*tmp, ' ');
    free(*tmp);
    *tmp = NULL;
    context.rgb_matrix = NULL;
    if (matrix_length(context.matrix) != 2)
        return (free_parser_rgb(context), perror_and_exit(cube3d, "Invalid RGB format: Expected '<F/C> <R,G,B>'", 1));
    if (!is_valid_str_rgb(context.matrix[1]))
        return (free_parser_rgb(context), perror_and_exit(cube3d, "Invalid RGB characters: Only digits and commas are allowed", 1));
    context.rgb_matrix = ft_split(context.matrix[1], ',');
    if (matrix_length(context.rgb_matrix) != 3)
        return (free_parser_rgb(context), perror_and_exit(cube3d, "Invalid RGB format: Expected exactly 3 values separated by commas", 1));
    context.rgb = malloc(sizeof(int) * 3);
    rgb_atoi(context);
    if (!is_valid_rgb(context.rgb, 3))
        return (free_parser_rgb(context), perror_and_exit(cube3d, "Invalid RGB range: Values must be between 0 and 255", 1));
    set_rgb(cube3d, context);
    free_parser_rgb(context);
}
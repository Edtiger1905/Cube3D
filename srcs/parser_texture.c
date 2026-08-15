#include "cube3d.h"

typedef struct s_context
{
    char **matrix;
    t_cube3d *cube3d;
} t_context;

static void free_parser_texture(t_context context)
{
    if (context.matrix)
        free_matrix(context.matrix);
}

static void set_texture(t_context context, void **texture)
{
    int width;
    int height;
    void *img_ptr;

    if (*texture)
        return (free_parser_texture(context), perror_and_exit(context.cube3d, "Duplicate texture configuration: Texture ID is already set", 1));
    img_ptr = mlx_xpm_file_to_image(context.cube3d->mlx_ptr, context.matrix[1], &width, &height);
    if (!img_ptr)
        return (free_parser_texture(context), perror_and_exit(context.cube3d, "Invalid XPM file: Could not load the image with MiniLibX", 1));
    *texture = img_ptr;
}

void parser_texture(t_cube3d *cube3d, char **tmp)
{
    int fd;
    t_context context;

    context.cube3d = cube3d;
    context.matrix = ft_split(*tmp, ' ');
    free(*tmp);
    *tmp = NULL;
    if (matrix_length(context.matrix) != 2)
        return (free_parser_texture(context), perror_and_exit(cube3d, "Invalid texture format: Expected '<ID> <path_to_texture>'", 1));

    fd = open(context.matrix[1], O_RDONLY);
    if (fd < 0)
        return (free_parser_texture(context), perror_and_exit(cube3d, "Texture file error: Cannot open or find the specified file", 1));
    close(fd);

    if (ft_strncmp(context.matrix[0], "NO", 2) == 0)
        set_texture(context, &context.cube3d->textures.north);
    else if (ft_strncmp(context.matrix[0], "SO", 2) == 0)
        set_texture(context, &context.cube3d->textures.south);
    else if (ft_strncmp(context.matrix[0], "EA", 2) == 0)
        set_texture(context, &context.cube3d->textures.east);
    else if (ft_strncmp(context.matrix[0], "WE", 2) == 0)
        set_texture(context, &context.cube3d->textures.west);

    free_parser_texture(context);
}
#include "cube3d.h"

void init_textures(t_cube3d *cube3d)
{
    char *tmp;
    char *line;
    t_textures textures;

    textures.north = NULL;
    textures.south = NULL;
    textures.east = NULL;
    textures.west = NULL;
    textures.floor = -1;
    textures.ceiling = -1;
    cube3d->textures = textures;
    while ((line = get_next_line(cube3d->fd)))
    {
        tmp = ft_strtrim(line, "\n");
        free(line);
        if (ft_strncmp(tmp, "NO", 2) == 0)
            parser_texture(cube3d, &tmp);
        else if (ft_strncmp(tmp, "SO", 2) == 0)
            parser_texture(cube3d, &tmp);
        else if (ft_strncmp(tmp, "EA", 2) == 0)
            parser_texture(cube3d, &tmp);
        else if (ft_strncmp(tmp, "WE", 2) == 0)
            parser_texture(cube3d, &tmp);
        else if (ft_strncmp(tmp, "F", 1) == 0)
            parser_rgb(cube3d, &tmp);
        else if (ft_strncmp(tmp, "C", 1) == 0)
            parser_rgb(cube3d, &tmp);
        free(tmp);
    }
}
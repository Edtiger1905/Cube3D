#include "cube3d.h"

void init_textures(t_cube3d *cube3d)
{
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
        if (ft_strncmp(line, "NO", 2) == 0)
            parser_texture(cube3d, &line);
        else if (ft_strncmp(line, "SO", 2) == 0)
            parser_texture(cube3d, &line);
        else if (ft_strncmp(line, "EA", 2) == 0)
            parser_texture(cube3d, &line);
        else if (ft_strncmp(line, "WE", 2) == 0)
            parser_texture(cube3d, &line);
        else if (ft_strncmp(line, "F", 1) == 0)
            parser_rgb_texture(cube3d, &line);
        else if (ft_strncmp(line, "C", 1) == 0)
            parser_rgb_texture(cube3d, &line);
        if (line)
            free(line);
    }
}

#include "cube3d.h"

int is_cub(char *src_map)
{
    char *s;

    s = ft_strrchr(src_map, '.');

    if (!s || ft_strlen(s) > 4 || ft_strncmp(s, ".cub", 4) != 0)
        return 0;

    return 1;
}
#include "cube3d.h"

int is_valid_str_rgb(char *str_rgb)
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

int is_valid_rgb(int *rgb, int len)
{
    int i;

    i = 0;
    while (i < len)
    {
        if (rgb[i] < 0 || rgb[i] > 255)
            return (0);
        i++;
    }
    return (1);
}
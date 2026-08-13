#include "cube3d.h"

static int is_cub(char *src_map)
{
    char *s;

    s = ft_strrchr(src_map, '.');

    if (!s || ft_strlen(s) > 4 || ft_strncmp(s, ".cub", 4) != 0)
        return (0);

    return (1);
}

int validate_and_return_fd(int argc, char **argv)
{
    int fd;
    char *src_map;

    if (argc < 2)
        perror_and_exit(NULL, "[VALIDATOR] please set the path of the map ", 1);
    if (argc > 2)
        perror_and_exit(NULL, "[VALIDATOR] please set only the path of the map ", 1);
    src_map = argv[1];
    if (!is_cub(src_map))
        perror_and_exit(NULL, "[VALIDATOR] file must finish with .cub extension", 1);
    fd = open(src_map, O_RDONLY);
    if (fd < 0)
        perror_and_exit(NULL, "[VALIDATOR] file not open", 1);
    return (fd);
}
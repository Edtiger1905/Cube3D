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
        perror_and_exit(NULL, "Missing argument: Please provide a map file", 1);
    if (argc > 2)
        perror_and_exit(NULL, "Too many arguments: Only one map file is allowed", 1);
    src_map = argv[1];
    if (!is_cub(src_map))
        perror_and_exit(NULL, "Invalid file extension: Map must end with '.cub'", 1);
    fd = open(src_map, O_RDONLY);
    if (fd < 0)
        perror_and_exit(NULL, "File error: Cannot open the map file", 1);
    return (fd);
}
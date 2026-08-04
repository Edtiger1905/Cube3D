#include "cube3d.h"

int main(int argc, char **argv)
{
    char *src_map;

    if (argc != 2)
        putstr_error_and_exit("Please set the path of the map", 1);

    src_map = argv[1];

    if (!is_cub(src_map))
        putstr_error_and_exit("File must finish with .cub extension", 1);

    return 0;
}
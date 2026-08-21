#include "cube3d.h"

int main(int argc, char **argv)
{
    t_cube3d cube3d;

    cube3d.argc = argc;
    cube3d.argv = argv;
    init_cube3d(&cube3d);
    free_cube3d(&cube3d);
    return (0);
}
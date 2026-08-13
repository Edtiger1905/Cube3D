#include "cube3d.h"

int main(int argc, char **argv)
{
    t_cube3d cube3d;

    cube3d = init_cube3d(argc, argv);
    free_cube3d(&cube3d);
    return (0);
}
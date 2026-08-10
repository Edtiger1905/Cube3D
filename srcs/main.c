#include "cube3d.h"

int main(int argc, char **argv)
{
    t_cube3d cube3d;

    cube3d.fd = validate_argv_and_return_fd(argc, argv);
    return 0;
}
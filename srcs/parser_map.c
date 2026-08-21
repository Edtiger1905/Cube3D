#include "cube3d.h"

static void free_helper(char *tmp, char *line)
{
    if (tmp)
        free(tmp);
    if (line)
        free(line);
}

static void calculate_map_lines(t_cube3d *cube3d)
{
    char *tmp;
    char *line;
    int lines;
    int start_read_map;

    if (cube3d->fd >= 0)
        return perror_and_exit(cube3d, "[PARSER MAP] Please close fd before read map");
    open_file_and_setconfig(cube3d);
    lines = 0;
    start_read_map = 0;
    while ((line = get_next_line(cube3d->fd)))
    {
        tmp = ft_strtrim(line, "\n");
        if (is_map(tmp))
        {
            lines++;
            start_read_map = 1;
        }
        if (!is_map(tmp) && start_read_map == 1)
            return (free_helper(tmp, line), perror_and_exit(cube3d, "[PARSER MAP] Invalid map line"));
        free_helper(tmp, line);
    }
    close(cube3d->fd);
    cube3d->fd = -1;
    cube3d->map.lines = lines;
}

static void set_matrix(t_cube3d *cube3d)
{
    int i;
    char *tmp;
    char *line;
    int start_read_map;

    if (cube3d->fd >= 0)
        return perror_and_exit(cube3d, "[PARSER MAP] Please close fd before read map");
    open_file_and_setconfig(cube3d);
    start_read_map = 0;
    i = 0;
    while ((line = get_next_line(cube3d->fd)))
    {
        tmp = ft_strtrim(line, "\n");
        if (is_map(tmp) && i < cube3d->map.lines)
        {
            cube3d->map.matrix[i] = ft_strdup(tmp);
            i++;
            start_read_map = 1;
        }
        if (!is_map(tmp) && start_read_map == 1)
            return (free_helper(tmp, line), perror_and_exit(cube3d, "[PARSER MAP] Invalid map line"));
        free_helper(tmp, line);
    }
    close(cube3d->fd);
    cube3d->fd = -1;
}

void print_map(t_cube3d *cube3d)
{
    int i;
    if (!cube3d || !cube3d->map.matrix)
        return;
    i = 0;
    printf("\n--- START OF THE MAP ---\n");
    while (cube3d->map.matrix[i])
    {
        printf("%s\n", cube3d->map.matrix[i]);
        i++;
    }
    printf("--- END OF THE MAP (%d lines) ---\n\n", i);
}

void parser_map(t_cube3d *cube3d)
{
    cube3d->map.lines = 0;
    cube3d->map.matrix = NULL;
    calculate_map_lines(cube3d);
    cube3d->map.matrix = ft_calloc(cube3d->map.lines + 1, sizeof(char *));
    if (!cube3d->map.matrix)
        perror_and_exit(cube3d, "[PARSER MAP] Failed to initialize matrix");
    set_matrix(cube3d);
    print_map(cube3d);
}
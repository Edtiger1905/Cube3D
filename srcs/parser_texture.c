#include "cube3d.h"

/*
    ----------  TEXTURES    ----------
    Durante il ciclo in init_textures, se viene identificata una stringa
    corrispondente a una texture (NO, SO, EA, WE), viene chiamata parser_texture.
    Questa funzione esegue un primo parsing rimuovendo il '\n' tramite ft_strtrim,
    seguito da uno split per separare l'identificatore (es. "NO") dal percorso del file.
    Dopo aver verificato che ci siano esattamente due elementi e che il file esista,
    la funzione set_texture si occupa di caricare l'immagine XPM e salvarne
    il puntatore nell'attributo corrispondente della struttura t_textures.
*/

static void duplicate_texture_error(t_cube3d *cube3d, char **matrix, void *img_ptr)
{
    if (img_ptr)
        mlx_destroy_image(cube3d->mlx_ptr, img_ptr);
    free_matrix_and_flush_gnl(cube3d, matrix);
    perror_and_exit(cube3d, "[PARSER TEXTURE] duplicate texture", 1);
}

static void set_texture(t_cube3d *cube3d, char **matrix)
{
    void *img_ptr;

    img_ptr = mlx_xpm_file_to_image(cube3d->mlx_ptr, matrix[1], &cube3d->width, &cube3d->height);
    if (!img_ptr)
        (free_matrix_and_flush_gnl(cube3d, matrix), perror_and_exit(cube3d, "[PARSER TEXTURE] invalid or corrupted xmp file", 1));
    if (ft_strncmp(matrix[0], "NO", 2) == 0)
    {
        if (cube3d->textures.north)
            duplicate_texture_error(cube3d, matrix, img_ptr);
        cube3d->textures.north = img_ptr;
    }
    else if (ft_strncmp(matrix[0], "SO", 2) == 0)
    {
        if (cube3d->textures.south)
            duplicate_texture_error(cube3d, matrix, img_ptr);
        cube3d->textures.south = img_ptr;
    }
    else if (ft_strncmp(matrix[0], "EA", 2) == 0)
    {
        if (cube3d->textures.east)
            duplicate_texture_error(cube3d, matrix, img_ptr);
        cube3d->textures.east = img_ptr;
    }
    else if (ft_strncmp(matrix[0], "WE", 2) == 0)
    {
        if (cube3d->textures.west)
            duplicate_texture_error(cube3d, matrix, img_ptr);
        cube3d->textures.west = img_ptr;
    }
}

void parser_texture(t_cube3d *cube3d, char **line)
{
    int texture_fd;
    char *tmp;
    char **matrix;

    tmp = ft_strtrim(*line, "\n");
    free(*line);
    *line = NULL;
    matrix = ft_split(tmp, ' ');
    free(tmp);
    if (matrix_length(matrix) != 2)
        (free_matrix_and_flush_gnl(cube3d, matrix), perror_and_exit(cube3d, "[PARSER TEXTURE] cardinal point texture must be 'X path_of_texture'", 1));
    texture_fd = open(matrix[1], O_RDONLY);
    if (texture_fd < 0)
        (free_matrix_and_flush_gnl(cube3d, matrix), perror_and_exit(cube3d, "[PARSER TEXTURE] file not open", 1));
    close(texture_fd);
    set_texture(cube3d, matrix);
    free_matrix(matrix);
}
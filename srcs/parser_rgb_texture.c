#include "cube3d.h"

/*
    ----------  RGB    ----------
    Nel ciclo di init_textures, se viene trovato un identificatore per il colore
    del pavimento (F) o del soffitto (C), si procede con parser_rgb.
    Vengono effettuati controlli rigorosi per assicurarsi che i valori RGB
    siano composti solo da numeri separati da virgole e che rientrino nel range [0, 255].
    Infine, i tre valori vengono combinati in un singolo intero (tramite bit shifting)
    e salvati nella struttura t_textures.
*/
static int is_valid_str_rgb(char *s)
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(s);

    while (i < len)
    {
        if (!(ft_isdigit(s[i]) || s[i] == ','))
            return 0;
        i++;
    }
    return 1;
}

static void fill_n_matrix(int *n_matrix, char **n_str_matrix)
{
    int i;
    int matrix_len;

    i = 0;
    matrix_len = matrix_length(n_str_matrix);
    while (i < matrix_len)
    {
        n_matrix[i] = ft_atoi(n_str_matrix[i]);
        i++;
    }
}

static int is_valid_n_rgb(int *n_matrix, int len)
{
    int i;

    i = 0;
    while (i < len)
    {
        if (n_matrix[i] < 0 || n_matrix[i] > 255)
            return (0);
        i++;
    }
    return (1);
}

static void duplicate_rgb_texture_error(t_cube3d *cube3d, char **matrix, int *n_matrix)
{
    free_matrix_and_flush_gnl(cube3d, matrix);
    free(n_matrix);
    perror_and_exit(cube3d, "[PARSER RGB] duplicate rgb texture", 1);
}

static void set_rgb_texture(t_cube3d *cube3d, char **matrix, int *n_matrix)
{
    int R;
    int G;
    int B;
    int rgb_color;

    R = n_matrix[0];
    G = n_matrix[1];
    B = n_matrix[2];
    rgb_color = (R << 16) | (G << 8) | B;
    if (ft_strncmp(matrix[0], "F", 1) == 0)
    {
        if (cube3d->textures.floor != -1)
            duplicate_rgb_texture_error(cube3d, matrix, n_matrix);
        cube3d->textures.floor = rgb_color;
    }
    else if (ft_strncmp(matrix[0], "C", 1) == 0)
    {
        if (cube3d->textures.ceiling != -1)
            duplicate_rgb_texture_error(cube3d, matrix, n_matrix);
        cube3d->textures.ceiling = rgb_color;
    }
}

void parser_rgb_texture(t_cube3d *cube3d, char **line)
{
    char *tmp;
    char **matrix;
    char **n_str_matrix;
    int *n_matrix;

    tmp = ft_strtrim(*line, "\n");
    free(*line);
    *line = NULL;
    matrix = ft_split(tmp, ' ');
    free(tmp);
    if (matrix_length(matrix) != 2)
        (free_matrix_and_flush_gnl(cube3d, matrix), perror_and_exit(cube3d, "[PARSER RGB] color must be 'X r,g,b'", 1));
    if (!is_valid_str_rgb(matrix[1]))
        (free_matrix_and_flush_gnl(cube3d, matrix), perror_and_exit(cube3d, "[PARSER RGB] rgb must be composed by numbers and separated by ','", 1));
    n_str_matrix = ft_split(matrix[1], ',');
    if (matrix_length(n_str_matrix) != 3)
        (free_matrix_and_flush_gnl(cube3d, matrix), free_matrix(n_str_matrix), perror_and_exit(cube3d, "[PARSER RGB] rgb must be composed with 3 numbers separated by ','", 1));
    n_matrix = malloc(3 * sizeof(int));
    fill_n_matrix(n_matrix, n_str_matrix);
    free_matrix(n_str_matrix);
    if (!is_valid_n_rgb(n_matrix, 3))
        (free_matrix_and_flush_gnl(cube3d, matrix), free(n_matrix), perror_and_exit(cube3d, "[PARSER RGB] rgb must composed by numbers between 0-255", 1));
    set_rgb_texture(cube3d, matrix, n_matrix);
    free(n_matrix);
    free_matrix(matrix);
}
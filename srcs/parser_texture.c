#include "cube3d.h"

/*
** ============================================================================
** PARSING DELLE TEXTURE (NORD, SUD, EST, OVEST)
** ============================================================================
** Questo file si occupa di processare le righe di configurazione relative
** ai percorsi delle texture dei muri.
**
** Flusso di esecuzione (es. input: "NO ./textures/north.xpm"):
** 1. Pulizia e divisione: La riga viene ripulita dal newline ('\n') e
**    separata tramite lo spazio -> matrix = {"NO", "./textures/north.xpm"}.
** 2. Controllo formato: Si verifica che la riga contenga esattamente due
**    elementi: l'Identificativo e il Percorso.
** 3. Validazione file: La funzione `exist_texture` prova ad aprire il file
**    nel percorso indicato in sola lettura, per garantire che esista.
** 4. Routing e caricamento: `parser_texture_controller` individua l'ID
**    ("NO", "SO", "EA", "WE"). Successivamente, `set_texture` controlla
**    che la texture non sia già stata impostata (evitando duplicati) e
**    utilizza la MiniLibX (`mlx_xpm_file_to_image`) per caricare il file
**    XPM in memoria, salvandone il puntatore nella struttura principale.
** ============================================================================
*/

static void exist_texture(t_cube3d *cube3d, char **matrix)
{
    int fd;

    fd = open(matrix[1], O_RDONLY);
    if (fd < 0)
        (free_matrix(matrix)), perror_and_exit(cube3d, "[PARSER TEXTURE] Cannot open or find the texture file");
    close(fd);
}

static void set_texture(t_cube3d *cube3d, char **matrix, void **t)
{
    int width;
    int height;

    void *img_ptr;

    if (*t)
        (free_matrix(matrix), perror_and_exit(cube3d, "[PARSER TEXTURE] Duplicate texture"));

    img_ptr = mlx_xpm_file_to_image(cube3d->mlx_ptr, matrix[1], &width, &height);
    if (!img_ptr)
        (free_matrix(matrix), perror_and_exit(cube3d, "[PARSER TEXTURE] Could not load the image with MiniLibX"));

    *t = img_ptr;
}

static void parser_texture_controller(t_cube3d *cube3d, char **matrix)
{
    if (ft_strncmp(matrix[0], "NO", 2) == 0)
        set_texture(cube3d, matrix, &cube3d->textures.north);
    else if (ft_strncmp(matrix[0], "SO", 2) == 0)
        set_texture(cube3d, matrix, &cube3d->textures.south);
    else if (ft_strncmp(matrix[0], "EA", 2) == 0)
        set_texture(cube3d, matrix, &cube3d->textures.east);
    else if (ft_strncmp(matrix[0], "WE", 2) == 0)
        set_texture(cube3d, matrix, &cube3d->textures.west);
}

void parser_texture(t_cube3d *cube3d, char *line)
{
    char *tmp;
    char **matrix;

    tmp = ft_strtrim(line, "\n");
    matrix = ft_split(tmp, ' ');
    free(tmp);
    free(line);
    if (matrix_length(matrix) != 2)
        (free_matrix(matrix), perror_and_exit(cube3d, "[PARSER TEXTURE] Expected '<ID> <path_to_texture>'"));
    exist_texture(cube3d, matrix);
    parser_texture_controller(cube3d, matrix);
    free_matrix(matrix);
}
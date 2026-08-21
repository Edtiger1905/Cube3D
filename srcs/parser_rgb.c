#include "cube3d.h"

/*
** ============================================================================
** PARSING DEI COLORI (PAVIMENTO E SOFFITTO)
** ============================================================================
** Questo file gestisce l'estrazione, la validazione e la conversione dei
** colori in formato RGB per il pavimento (F) e il soffitto (C).
**
** Flusso di esecuzione (es. input: "F 220,100,0"):
** 1. Divisione iniziale: La riga viene ripulita dal newline e separata in un
**    array di due stringhe basato sullo spazio -> matrix = {"F", "220,100,0"}.
** 2. Validazione sintattica: Si verifica che il secondo elemento contenga
**    esclusivamente numeri e virgole (nessun carattere estraneo).
** 3. Divisione RGB: Il blocco dei numeri viene ulteriormente diviso usando
**    la virgola come delimitatore -> rgb_matrix = {"220", "100", "0"}.
** 4. Conversione e range: Tramite `convert_rgb_values` (che usa ft_atoi),
**    le stringhe diventano interi. Si verifica che ogni singolo valore sia
**    correttamente compreso nel range valido [0, 255].
** 5. Codifica bit a bit: In `set_rgb`, i tre valori vengono uniti in un
**    singolo numero intero tramite bit-shifting: (R << 16) | (G << 8) | B.
**    Il risultato finale viene salvato nella struttura principale, bloccando
**    immediatamente eventuali doppioni (es. due configurazioni per 'F').
** ============================================================================
*/

typedef struct s_context
{
    int *rgb;
    char **matrix;
    char **rgb_matrix;

    t_cube3d *cube3d;
} t_context;

static void free_helper(t_context *context)
{
    if (context->rgb)
        free(context->rgb);
    if (context->matrix)
        free_matrix(context->matrix);
    if (context->rgb_matrix)
        free_matrix(context->rgb_matrix);
}

static int is_valid_str_rgb(char *str_rgb)
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(str_rgb);
    while (i < len)
    {
        if (!(ft_isdigit(str_rgb[i]) || str_rgb[i] == ','))
            return (0);
        i++;
    }
    return (1);
}

static void convert_rgb_values(t_context *context)
{
    int i;
    int rgb_matrix_len;

    i = 0;
    rgb_matrix_len = matrix_length(context->rgb_matrix);
    while (i < rgb_matrix_len)
    {
        context->rgb[i] = ft_atoi(context->rgb_matrix[i]);
        if (context->rgb[i] < 0 || context->rgb[i] > 255)
            return (free_helper(context), perror_and_exit(context->cube3d, "Invalid RGB range: Values must be between 0 and 255"));
        i++;
    }
}

static void set_rgb(t_context *context)
{
    int R;
    int G;
    int B;
    int rgb_color;

    R = context->rgb[0];
    G = context->rgb[1];
    B = context->rgb[2];
    rgb_color = (R << 16) | (G << 8) | B;
    if (ft_strncmp(context->matrix[0], "F", 1) == 0)
    {
        if (context->cube3d->textures.floor != -1)
            return (free_helper(context), perror_and_exit(context->cube3d, "Duplicate RGB configuration: Floor color is already set"));
        context->cube3d->textures.floor = rgb_color;
    }
    if (ft_strncmp(context->matrix[0], "C", 1) == 0)
    {
        if (context->cube3d->textures.ceiling != -1)
            return (free_helper(context), perror_and_exit(context->cube3d, "Duplicate RGB configuration: Floor color is already set"));
        context->cube3d->textures.ceiling = rgb_color;
    }
}

void parser_rgb(t_cube3d *cube3d, char *line)
{
    char *tmp;
    t_context context;

    context.rgb = NULL;
    context.matrix = NULL;
    context.rgb_matrix = NULL;
    context.cube3d = cube3d;
    tmp = ft_strtrim(line, "\n");
    context.matrix = ft_split(tmp, ' ');
    free(tmp);
    free(line);
    if (matrix_length(context.matrix) != 2)
        return (free_helper(&context), perror_and_exit(cube3d, "Invalid RGB format: Expected '<F/C> <R,G,B>'"));
    if (!is_valid_str_rgb(context.matrix[1]))
        return (free_helper(&context), perror_and_exit(cube3d, "Invalid RGB characters: Only digits and commas are allowed'"));
    context.rgb = malloc(sizeof(int) * 3);
    if (!context.rgb)
        return (free_helper(&context), perror_and_exit(cube3d, "Malloc error: Failed to initialize RGB"));
    context.rgb_matrix = ft_split(context.matrix[1], ',');
    if (matrix_length(context.rgb_matrix) != 3)
        return (free_helper(&context), perror_and_exit(cube3d, "Invalid RGB format: Expected exactly 3 values separated by commas"));
    convert_rgb_values(&context);
    set_rgb(&context);
    free_helper(&context);
}
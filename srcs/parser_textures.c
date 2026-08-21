#include "cube3d.h"

/*
** ============================================================================
** CONTROLLER PRINCIPALE DEL PARSING (TEXTURES & COLORI)
** ============================================================================
** Questo file funge da punto d'ingresso per la lettura e l'estrazione delle
** configurazioni iniziali della mappa, ovvero tutto ciò che si trova prima
** della griglia della mappa vera e propria.
**
** Flusso di esecuzione:
** 1. Inizializzazione: `init_empty_textures` imposta tutti i puntatori
**    delle texture a NULL e i colori a -1 (usato come flag per indicare
**    che un colore non è ancora stato assegnato).
** 2. Lettura del file: Il file .cub viene aperto (`open_file_and_setconfig`)
**    e letto riga per riga utilizzando `get_next_line`.
** 3. Smistamento (Routing):
**    - Se la riga inizia con un identificativo di direzione ("NO", "SO",
**      "EA", "WE"), la sua elaborazione viene delegata a `parser_texture`.
**    - Se la riga inizia con "F" o "C", viene delegata a `parser_rgb`.
**    - Le altre righe (es. righe vuote) vengono ignorate per il momento e
**      liberate.
** 4. Conclusione: Al termine della lettura, il file descriptor viene chiuso.
**    In un secondo momento (fuori da questo file) il programma riaprirà il
**    file o sfrutterà i dati salvati per parsare la griglia della mappa.
** ============================================================================
*/

void parser_textures(t_cube3d *cube3d)
{
    char *line;

    open_file_and_setconfig(cube3d);
    while ((line = get_next_line(cube3d->fd)))
    {
        if (ft_strncmp(line, "NO", 2) == 0 ||
            ft_strncmp(line, "SO", 2) == 0 ||
            ft_strncmp(line, "EA", 2) == 0 ||
            ft_strncmp(line, "WE", 2) == 0)
        {
            parser_texture(cube3d, line);
            continue;
        }
        if (ft_strncmp(line, "F", 1) == 0 ||
            ft_strncmp(line, "C", 1) == 0)
        {
            parser_rgb(cube3d, line);
            continue;
        }
        free(line);
    }
    close(cube3d->fd);
    cube3d->fd = -1;
}
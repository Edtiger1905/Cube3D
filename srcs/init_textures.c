#include "cube3d.h"

/*
    PARSING DELLE TEXTURE E COLORI

    Allora, la funzione init_textures ha come obbiettivo grazie a parser_loop, parser_texture e parser_rgb di
    leggere le righe, trovare coincidenze ad esempio "NO ./textures/north.xmp9", appena legge "NO" chiama a parser_texture.
    Leggi "parser_texture.c" e "parser_rgb.c" per capire come funzionano. Dopo aver letto fa un controllo per sapere se quello
    che sta leggendo non e' piu' un texture se no che e' una linea della mappa, in quel momento controlla se ci sono tutte le textures
    e manda un errore in caso di mancanza di qualcuna, altrimenti chiude il file (Questo perche' cosi al leggere la mappa
    leggiamo di nuovo il file e quando troviamo quella coincidenza iniziamo a fare il parsing della mappa) e si chiude il ciclo
*/

static int are_textures_completed(t_textures textures)
{
    if (!textures.north || !textures.south || !textures.east || !textures.west || textures.floor == -1 || textures.ceiling == -1)
        return (0);
    return (1);
}

static void parser_loop(t_cube3d *cube3d, char *line)
{
    char *tmp;

    tmp = ft_strtrim(line, "\n");
    free(line);
    if (ft_strncmp(tmp, "NO", 2) == 0)
        parser_texture(cube3d, &tmp);
    else if (ft_strncmp(tmp, "SO", 2) == 0)
        parser_texture(cube3d, &tmp);
    else if (ft_strncmp(tmp, "EA", 2) == 0)
        parser_texture(cube3d, &tmp);
    else if (ft_strncmp(tmp, "WE", 2) == 0)
        parser_texture(cube3d, &tmp);
    else if (ft_strncmp(tmp, "F", 1) == 0)
        parser_rgb(cube3d, &tmp);
    else if (ft_strncmp(tmp, "C", 1) == 0)
        parser_rgb(cube3d, &tmp);
    else if (is_map(tmp))
    {
        if (!are_textures_completed(cube3d->textures))
            return (free(tmp), perror_and_exit(cube3d, "Invalid map: Textures are not completed", 1));
        cube3d->textures.textures_completed = 1;
        close(cube3d->fd);
    }
    free(tmp);
}

void init_textures(t_cube3d *cube3d)
{
    char *line;

    cube3d->textures.north = NULL;
    cube3d->textures.south = NULL;
    cube3d->textures.east = NULL;
    cube3d->textures.west = NULL;
    cube3d->textures.floor = -1;
    cube3d->textures.ceiling = -1;
    cube3d->textures.textures_completed = 0;
    while ((line = get_next_line(cube3d->fd)))
    {
        parser_loop(cube3d, line);
        if (cube3d->textures.textures_completed == 1)
            break;
    }
}
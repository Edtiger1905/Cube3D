#ifndef CUBE3D_H
# define CUBE3D_H

# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_map
{
	int			lines;

	char		**matrix;
}				t_map;

typedef struct s_textures
{
	void		*north;
	void		*south;
	void		*east;
	void		*west;

	int			floor;
	int			ceiling;
}				t_textures;

typedef struct s_cube3d
{
	int			argc;
	char		**argv;

	int			fd;
	char		*src_map;

	void		*mlx_ptr;

	t_textures	textures;

	t_map		map;
}				t_cube3d;

// free_memory.c
void			flush_gnl(t_cube3d *cube3d);
void			free_cube3d(t_cube3d *cube3d);
void			free_matrix(char **matrix);

// init_cube3d.c
void			init_cube3d(t_cube3d *cube3d);

// init_map.c
void			init_map(t_cube3d *cube3d);

// init_textures.c
void			init_textures(t_cube3d *cube3d);

// open_file.c
void			open_file(t_cube3d *cube3d);

// parser_rgb.c
void			parser_rgb(t_cube3d *cube3d, char *line);

// parser_texture.c
void			parser_texture(t_cube3d *cube3d, char *line);

// utils.c
void			free_and_exit(t_cube3d *cube3d, char *msg);
int				is_map(char *line);
int				matrix_length(char **matrix);
int				is_valid_rgb_number(int *rgb, int len);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epandele <epandele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 12:00:00 by epandele          #+#    #+#             */
/*   Updated: 2026/09/11 17:39:13 by epandele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "get_next_line.h"
# include "libft.h"
# include <mlx.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_player
{
	int			x;
	int			y;
}				t_player;

typedef struct s_map
{
	int			lines;

	char		**matrix;
	t_player	player;
}				t_map;

typedef struct s_texdim
{
	int			w;
	int			h;
}				t_texdim;

typedef struct s_textures
{
	void		*north;
	void		*south;
	void		*east;
	void		*west;

	t_texdim	north_d;
	t_texdim	south_d;
	t_texdim	east_d;
	t_texdim	west_d;

	int			floor;
	int			ceiling;
}				t_textures;

typedef struct s_cam
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_cam;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_img;

typedef struct s_ray
{
	double		ray_dir_x;
	double		ray_dir_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_x;
	double		side_dist_y;
	double		perp_wall_dist;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			side;
}				t_ray;

typedef struct s_slice
{
	int			x;
	int			tex_x;
	int			start;
	int			end;
	int			line_h;
}				t_slice;

typedef struct s_pt
{
	int			x;
	int			y;
}				t_pt;

typedef struct s_stack
{
	t_pt		*data;
	int			top;
}				t_stack;

typedef struct s_cube3d
{
	int			argc;
	char		**argv;

	int			fd;
	char		*src_map;

	void		*mlx_ptr;
	void		*win_ptr;
	t_img		screen;
	t_cam		cam;

	t_textures	textures;

	t_map		map;
}				t_cube3d;

# define WIN_WIDTH 1024
# define WIN_HEIGHT 768
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

/* free_memory.c */
void			flush_gnl(t_cube3d *cube3d);
void			free_cube3d(t_cube3d *cube3d);
void			free_matrix(char **matrix);

/* init_cube3d.c */
void			init_cube3d(t_cube3d *cube3d);

/* init_map.c */
void			init_map(t_cube3d *cube3d);

/* check_map.c */
void			check_map_closed(t_cube3d *cube3d);

/* init_textures.c */
void			init_textures(t_cube3d *cube3d);

/* open_file.c */
void			open_file(t_cube3d *cube3d);

/* parser_rgb.c */
void			parser_rgb(t_cube3d *cube3d, char *line);

/* parser_texture.c */
void			parser_texture(t_cube3d *cube3d, char *line);

/* utils.c */
void			free_and_exit(t_cube3d *cube3d, char *msg);
int				is_map(char *line);
int				matrix_length(char **matrix);
int				is_valid_rgb_number(int *rgb, int len);
int				is_valid_str_rgb(char *str_rgb);

/* init_render.c */
void			init_render(t_cube3d *cube3d);

/* raycasting.c */
int				render_frame(void *param);

/* raycasting_draw.c */
void			draw_column(t_cube3d *cube3d, t_ray *ray, int x);

/* raycasting_utils.c */
int				is_wall(t_cube3d *cube3d, int x, int y);
void			put_pixel(t_img *dst, int x, int y, int color);
int				get_tex_color(t_img *tex, int tex_x, int tex_y);
void			draw_floor_ceiling(t_cube3d *cube3d, int x, int start,
					int end);

/* hooks.c */
int				handle_keypress(int keycode, void *param);
int				handle_close(void *param);

#endif
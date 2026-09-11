/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epandele <epandele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 12:00:00 by epandele          #+#    #+#             */
/*   Updated: 2026/09/11 17:32:32 by epandele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	select_texture(t_cube3d *cube3d, t_ray *ray, void **tex,
		t_texdim *dim)
{
	t_textures	*t;

	t = &cube3d->textures;
	if (ray->side == 0 && ray->ray_dir_x > 0)
	{
		*tex = t->west;
		*dim = t->west_d;
	}
	else if (ray->side == 0)
	{
		*tex = t->east;
		*dim = t->east_d;
	}
	else if (ray->ray_dir_y > 0)
	{
		*tex = t->north;
		*dim = t->north_d;
	}
	else
	{
		*tex = t->south;
		*dim = t->south_d;
	}
}

static int	compute_tex_x(t_cube3d *cube3d, t_ray *ray, int tex_w)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = cube3d->cam.pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = cube3d->cam.pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)tex_w);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		tex_x = tex_w - tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		tex_x = tex_w - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex_w)
		tex_x = tex_w - 1;
	return (tex_x);
}

static void	draw_wall_slice(t_cube3d *cube3d, t_img *tex, int tex_h,
		t_slice *slice)
{
	double	step;
	double	tex_pos;
	int		tex_y;
	int		y;

	step = (double)tex_h / (double)slice->line_h;
	tex_pos = (slice->start - WIN_HEIGHT / 2 + slice->line_h / 2) * step;
	y = slice->start;
	while (y < slice->end)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex_h)
			tex_y = tex_h - 1;
		tex_pos += step;
		put_pixel(&cube3d->screen, slice->x, y,
			get_tex_color(tex, slice->tex_x, tex_y));
		y++;
	}
}

void	draw_column(t_cube3d *cube3d, t_ray *ray, int x)
{
	t_img		tex;
	void		*tex_img;
	t_texdim	dim;
	t_slice		slice;

	slice.line_h = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	slice.start = -slice.line_h / 2 + WIN_HEIGHT / 2;
	if (slice.start < 0)
		slice.start = 0;
	slice.end = slice.line_h / 2 + WIN_HEIGHT / 2;
	if (slice.end >= WIN_HEIGHT)
		slice.end = WIN_HEIGHT - 1;
	select_texture(cube3d, ray, &tex_img, &dim);
	tex.addr = mlx_get_data_addr(tex_img, &tex.bpp, &tex.line_len,
			&tex.endian);
	slice.x = x;
	slice.tex_x = compute_tex_x(cube3d, ray, dim.w);
	if (slice.line_h > 0 && slice.start < slice.end)
		draw_wall_slice(cube3d, &tex, dim.h, &slice);
	draw_floor_ceiling(cube3d, x, slice.start, slice.end);
}
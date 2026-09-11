/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epandele <epandele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 12:00:00 by epandele          #+#    #+#             */
/*   Updated: 2026/09/11 17:32:51 by epandele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	is_wall(t_cube3d *cube3d, int x, int y)
{
	int		len;
	char	c;

	if (y < 0 || y >= cube3d->map.lines || x < 0)
		return (1);
	len = ft_strlen(cube3d->map.matrix[y]);
	if (x >= len)
		return (1);
	c = cube3d->map.matrix[y][x];
	if (c == '1' || c == ' ')
		return (1);
	return (0);
}

void	put_pixel(t_img *dst, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	pixel = dst->addr + (y * dst->line_len + x * (dst->bpp / 8));
	*(unsigned int *)pixel = (unsigned int)color;
}

int	get_tex_color(t_img *tex, int tex_x, int tex_y)
{
	char	*pixel;

	pixel = tex->addr + (tex_y * tex->line_len + tex_x * (tex->bpp / 8));
	return (*(unsigned int *)pixel);
}

void	draw_floor_ceiling(t_cube3d *cube3d, int x, int start, int end)
{
	int	y;

	y = 0;
	while (y < start)
		put_pixel(&cube3d->screen, x, y++, cube3d->textures.ceiling);
	y = end;
	while (y < WIN_HEIGHT)
		put_pixel(&cube3d->screen, x, y++, cube3d->textures.floor);
}
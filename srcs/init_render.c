/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epandele <epandele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 12:00:00 by epandele          #+#    #+#             */
/*   Updated: 2026/09/11 12:00:00 by epandele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	set_cam_ns(t_cube3d *cube3d, char c)
{
	if (c == 'N')
	{
		cube3d->cam.dir_x = 0;
		cube3d->cam.dir_y = -1;
		cube3d->cam.plane_x = 0.66;
		cube3d->cam.plane_y = 0;
	}
	else
	{
		cube3d->cam.dir_x = 0;
		cube3d->cam.dir_y = 1;
		cube3d->cam.plane_x = -0.66;
		cube3d->cam.plane_y = 0;
	}
}

static void	set_cam_ew(t_cube3d *cube3d, char c)
{
	if (c == 'E')
	{
		cube3d->cam.dir_x = 1;
		cube3d->cam.dir_y = 0;
		cube3d->cam.plane_x = 0;
		cube3d->cam.plane_y = 0.66;
	}
	else
	{
		cube3d->cam.dir_x = -1;
		cube3d->cam.dir_y = 0;
		cube3d->cam.plane_x = 0;
		cube3d->cam.plane_y = -0.66;
	}
}

static void	set_cam_from_char(t_cube3d *cube3d, char c)
{
	if (c == 'N' || c == 'S')
		set_cam_ns(cube3d, c);
	else
		set_cam_ew(cube3d, c);
}

static void	init_window(t_cube3d *cube3d)
{
	cube3d->win_ptr = mlx_new_window(cube3d->mlx_ptr, WIN_WIDTH,
			WIN_HEIGHT, "cub3D");
	if (!cube3d->win_ptr)
		free_and_exit(cube3d, "Failed to create window");
	cube3d->screen.img = mlx_new_image(cube3d->mlx_ptr, WIN_WIDTH,
			WIN_HEIGHT);
	if (!cube3d->screen.img)
		free_and_exit(cube3d, "Failed to create screen image");
	cube3d->screen.addr = mlx_get_data_addr(cube3d->screen.img,
			&cube3d->screen.bpp, &cube3d->screen.line_len,
			&cube3d->screen.endian);
}

void	init_render(t_cube3d *cube3d)
{
	char	orientation;
	char	*row;

	cube3d->cam.pos_x = cube3d->map.player.x + 0.5;
	cube3d->cam.pos_y = cube3d->map.player.y + 0.5;
	row = cube3d->map.matrix[cube3d->map.player.y];
	orientation = row[cube3d->map.player.x];
	set_cam_from_char(cube3d, orientation);
	init_window(cube3d);
	mlx_hook(cube3d->win_ptr, 17, 0, handle_close, cube3d);
	mlx_hook(cube3d->win_ptr, EVENT_KEYPRESS, MASK_KEYPRESS,
		handle_keydown, cube3d);
	mlx_hook(cube3d->win_ptr, EVENT_KEYRELEASE, MASK_KEYRELEASE,
		handle_keyup, cube3d);
	mlx_loop_hook(cube3d->mlx_ptr, render_frame, cube3d);
}

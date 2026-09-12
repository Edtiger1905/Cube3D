/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epandele <epandele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 12:00:00 by epandele          #+#    #+#             */
/*   Updated: 2026/09/12 12:00:00 by epandele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

#define MOVE_SPEED 0.05
#define ROT_SPEED 0.03

static void	try_move(t_cube3d *cube3d, double move_x, double move_y)
{
	double	new_x;
	double	new_y;

	new_x = cube3d->cam.pos_x + move_x;
	new_y = cube3d->cam.pos_y + move_y;
	if (!is_wall(cube3d, (int)new_x, (int)cube3d->cam.pos_y))
		cube3d->cam.pos_x = new_x;
	if (!is_wall(cube3d, (int)cube3d->cam.pos_x, (int)new_y))
		cube3d->cam.pos_y = new_y;
}

static void	rotate_cam(t_cube3d *cube3d, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cube3d->cam.dir_x;
	cube3d->cam.dir_x = cube3d->cam.dir_x * cos(angle)
		- cube3d->cam.dir_y * sin(angle);
	cube3d->cam.dir_y = old_dir_x * sin(angle)
		+ cube3d->cam.dir_y * cos(angle);
	old_plane_x = cube3d->cam.plane_x;
	cube3d->cam.plane_x = cube3d->cam.plane_x * cos(angle)
		- cube3d->cam.plane_y * sin(angle);
	cube3d->cam.plane_y = old_plane_x * sin(angle)
		+ cube3d->cam.plane_y * cos(angle);
}

void	update_movement(t_cube3d *cube3d)
{
	if (cube3d->keys.w)
		try_move(cube3d, cube3d->cam.dir_x * MOVE_SPEED,
			cube3d->cam.dir_y * MOVE_SPEED);
	if (cube3d->keys.s)
		try_move(cube3d, -cube3d->cam.dir_x * MOVE_SPEED,
			-cube3d->cam.dir_y * MOVE_SPEED);
	if (cube3d->keys.a)
		try_move(cube3d, cube3d->cam.dir_y * MOVE_SPEED,
			-cube3d->cam.dir_x * MOVE_SPEED);
	if (cube3d->keys.d)
		try_move(cube3d, -cube3d->cam.dir_y * MOVE_SPEED,
			cube3d->cam.dir_x * MOVE_SPEED);
	if (cube3d->keys.left)
		rotate_cam(cube3d, -ROT_SPEED);
	if (cube3d->keys.right)
		rotate_cam(cube3d, ROT_SPEED);
}

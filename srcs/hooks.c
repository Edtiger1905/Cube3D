/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epandele <epandele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 12:00:00 by epandele          #+#    #+#             */
/*   Updated: 2026/09/12 12:00:00 by epandele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	handle_close(void *param)
{
	t_cube3d	*cube3d;

	cube3d = (t_cube3d *)param;
	free_cube3d(cube3d);
	exit(0);
	return (0);
}

static void	set_key_state(t_cube3d *cube3d, int keycode, int value)
{
	if (keycode == KEY_W)
		cube3d->keys.w = value;
	else if (keycode == KEY_A)
		cube3d->keys.a = value;
	else if (keycode == KEY_S)
		cube3d->keys.s = value;
	else if (keycode == KEY_D)
		cube3d->keys.d = value;
	else if (keycode == KEY_LEFT)
		cube3d->keys.left = value;
	else if (keycode == KEY_RIGHT)
		cube3d->keys.right = value;
}

int	handle_keydown(int keycode, void *param)
{
	if (keycode == KEY_ESC)
		handle_close(param);
	set_key_state((t_cube3d *)param, keycode, 1);
	return (0);
}

int	handle_keyup(int keycode, void *param)
{
	set_key_state((t_cube3d *)param, keycode, 0);
	return (0);
}

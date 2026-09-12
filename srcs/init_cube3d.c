/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cube3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evera <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 13:57:56 by evera             #+#    #+#             */
/*   Updated: 2026/08/26 13:57:58 by evera            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	init_empty_cube3d(t_cube3d *cube3d)
{
	cube3d->fd = -1;
	cube3d->mlx_ptr = NULL;
	cube3d->win_ptr = NULL;
	cube3d->screen.img = NULL;
	cube3d->textures.north = NULL;
	cube3d->textures.south = NULL;
	cube3d->textures.east = NULL;
	cube3d->textures.west = NULL;
	cube3d->textures.floor = -1;
	cube3d->textures.ceiling = -1;
	cube3d->map.lines = 0;
	cube3d->map.matrix = NULL;
}

void	init_cube3d(t_cube3d *cube3d)
{
	init_empty_cube3d(cube3d);
	cube3d->mlx_ptr = mlx_init();
	if (!cube3d->mlx_ptr)
		free_and_exit(cube3d, "Failed to init mlx");
	init_textures(cube3d);
	init_map(cube3d);
	init_render(cube3d);
}

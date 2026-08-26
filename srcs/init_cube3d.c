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

void	init_cube3d(t_cube3d *cube3d)
{
	cube3d->fd = -1;
	cube3d->mlx_ptr = mlx_init();
	if (!cube3d->mlx_ptr)
		free_and_exit(cube3d, "Failed to init mlx");
	init_textures(cube3d);
	init_map(cube3d);
}

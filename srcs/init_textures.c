/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epandele <epandele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 12:00:00 by epandele          #+#    #+#             */
/*   Updated: 2026/09/11 18:00:15 by epandele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_textures(t_cube3d *cube3d)
{
	cube3d->textures.north = NULL;
	cube3d->textures.south = NULL;
	cube3d->textures.east = NULL;
	cube3d->textures.west = NULL;
	cube3d->textures.north_d.w = 0;
	cube3d->textures.north_d.h = 0;
	cube3d->textures.south_d.w = 0;
	cube3d->textures.south_d.h = 0;
	cube3d->textures.east_d.w = 0;
	cube3d->textures.east_d.h = 0;
	cube3d->textures.west_d.w = 0;
	cube3d->textures.west_d.h = 0;
	cube3d->textures.floor = -1;
	cube3d->textures.ceiling = -1;
}

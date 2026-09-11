/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epandele <epandele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 12:00:00 by epandele          #+#    #+#             */
/*   Updated: 2026/09/11 18:00:15 by epandele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	open_file(t_cube3d *cube3d)
{
	if (cube3d->argc < 2)
		free_and_exit(cube3d, "Missing map file");
	if (cube3d->fd >= 0)
		close(cube3d->fd);
	cube3d->fd = open(cube3d->argv[1], O_RDONLY);
	if (cube3d->fd < 0)
		free_and_exit(cube3d, "Failed to open map file");
}

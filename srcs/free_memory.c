/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epandele <epandele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 13:58:37 by evera             #+#    #+#             */
/*   Updated: 2026/09/11 17:34:25 by epandele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	flush_gnl(t_cube3d *cube3d)
{
	char	*line;

	if (cube3d->fd >= 0)
	{
		line = get_next_line(cube3d->fd);
		while (line)
		{
			free(line);
			line = get_next_line(cube3d->fd);
		}
		close(cube3d->fd);
		cube3d->fd = -1;
	}
}

void	free_cube3d(t_cube3d *cube3d)
{
	if (cube3d->mlx_ptr)
	{
		if (cube3d->textures.north)
			mlx_destroy_image(cube3d->mlx_ptr, cube3d->textures.north);
		if (cube3d->textures.south)
			mlx_destroy_image(cube3d->mlx_ptr, cube3d->textures.south);
		if (cube3d->textures.east)
			mlx_destroy_image(cube3d->mlx_ptr, cube3d->textures.east);
		if (cube3d->textures.west)
			mlx_destroy_image(cube3d->mlx_ptr, cube3d->textures.west);
		if (cube3d->screen.img)
			mlx_destroy_image(cube3d->mlx_ptr, cube3d->screen.img);
		if (cube3d->win_ptr)
			mlx_destroy_window(cube3d->mlx_ptr, cube3d->win_ptr);
		mlx_destroy_display(cube3d->mlx_ptr);
		free(cube3d->mlx_ptr);
	}
	flush_gnl(cube3d);
	if (cube3d->map.matrix)
		free_matrix(cube3d->map.matrix);
}

void	free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evera <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 14:15:06 by evera             #+#    #+#             */
/*   Updated: 2026/08/26 14:15:09 by evera            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	is_cardinal_point(char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "EA", 2) == 0 || ft_strncmp(line, "WE", 2) == 0)
		return (1);
	return (0);
}

static int	is_rgb_texture(char *line)
{
	if (ft_strncmp(line, "F", 1) == 0 || ft_strncmp(line, "C", 1) == 0)
		return (1);
	return (0);
}

void	init_textures(t_cube3d *cube3d)
{
	char	*line;

	cube3d->textures.north = NULL;
	cube3d->textures.south = NULL;
	cube3d->textures.east = NULL;
	cube3d->textures.west = NULL;
	cube3d->textures.floor = -1;
	cube3d->textures.ceiling = -1;
	open_file(cube3d);
	line = get_next_line(cube3d->fd);
	while (line)
	{
		if (is_map(line))
			return (free(line));
		else if (is_cardinal_point(line))
			parser_texture(cube3d, line);
		else if (is_rgb_texture(line))
			parser_rgb(cube3d, line);
		else
			free(line);
		line = get_next_line(cube3d->fd);
	}
}

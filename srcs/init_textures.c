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

static int	are_textures_completed(t_textures textures)
{
	if (!textures.north || !textures.south || !textures.east || !textures.west
		|| textures.floor == -1 || textures.ceiling == -1)
		return (0);
	return (1);
}

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

	open_file(cube3d);
	line = get_next_line(cube3d->fd);
	while (line)
	{
		if (is_map(line))
		{
			free(line);
			break ;
		}
		else if (is_cardinal_point(line))
			parser_texture(cube3d, line);
		else if (is_rgb_texture(line))
			parser_rgb(cube3d, line);
		else
			free(line);
		line = get_next_line(cube3d->fd);
	}
	if (!are_textures_completed(cube3d->textures))
		free_and_exit(cube3d, "Missing textures");
}

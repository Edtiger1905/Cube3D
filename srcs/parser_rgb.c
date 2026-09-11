/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_rgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epandele <epandele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 12:00:00 by epandele          #+#    #+#             */
/*   Updated: 2026/09/11 18:00:15 by epandele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	parse_rgb_value(char *str)
{
	int	value;

	if (!str || !*str)
		return (-1);
	if (!is_valid_str_rgb(str))
		return (-1);
	value = ft_atoi(str);
	if (value < 0 || value > 255)
		return (-1);
	return (value);
}

void	parser_rgb(t_cube3d *cube3d, char *line)
{
	char	**parts;
	char	**rgb;
	char	*id;
	int		values[3];
	int		idx;
	int		color;

	parts = ft_split(line, ' ');
	free(line);
	if (!parts || matrix_length(parts) != 2)
	{
		free_matrix(parts);
		free_and_exit(cube3d, "Invalid RGB format");
	}
	id = parts[0];
	if (ft_strlen(id) != 1 || (id[0] != 'F' && id[0] != 'C'))
	{
		free_matrix(parts);
		free_and_exit(cube3d, "Invalid RGB id");
	}
	idx = 0;
	while (idx < 3)
	{
		values[idx] = -1;
		idx++;
	}
	rgb = ft_split(parts[1], ',');
	free_matrix(parts);
	if (!rgb || matrix_length(rgb) != 3)
	{
		free_matrix(rgb);
		free_and_exit(cube3d, "Invalid RGB values");
	}
	idx = 0;
	while (idx < 3)
	{
		values[idx] = parse_rgb_value(rgb[idx]);
		if (values[idx] < 0)
		{
			free_matrix(rgb);
			free_and_exit(cube3d, "RGB out of range");
		}
		idx++;
	}
	color = (values[0] << 16) | (values[1] << 8) | values[2];
	free_matrix(rgb);
	if (id[0] == 'F')
		cube3d->textures.floor = color;
	else
		cube3d->textures.ceiling = color;
}

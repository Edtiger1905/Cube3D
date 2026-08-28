/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evera <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 14:02:29 by evera             #+#    #+#             */
/*   Updated: 2026/08/26 14:02:30 by evera            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	free_and_exit(t_cube3d *cube3d, char *msg)
{
	if (cube3d)
		free_cube3d(cube3d);
	ft_putstr_fd("Error:\n", 1);
	ft_putstr_fd(msg, 1);
	ft_putchar_fd('\n', 1);
	exit(1);
}

int	is_map(char *line)
{
	int	i;
	int	has_map_char;

	if (!line || !line[0])
		return (0);
	i = 0;
	has_map_char = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '0' && line[i] != '1' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
			&& line[i] != '\n')
			return (0);
		if (line[i] == '0' || line[i] == '1' || line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
			has_map_char = 1;
		i++;
	}
	return (has_map_char);
}

int	matrix_length(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix || !matrix[0])
		return (i);
	while (matrix[i])
		i++;
	return (i);
}

int	is_valid_rgb_number(int *rgb, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_str_rgb(char *str_rgb)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str_rgb);
	while (i < len)
	{
		if (!(ft_isdigit(str_rgb[i]) || str_rgb[i] == ','))
			return (0);
		i++;
	}
	return (1);
}

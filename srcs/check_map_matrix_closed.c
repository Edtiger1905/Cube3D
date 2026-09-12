/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evera <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 12:34:07 by evera             #+#    #+#             */
/*   Updated: 2026/09/12 12:34:09 by evera            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	is_on_border(char **matrix, int x, int y, int total_lines)
{
	if (y == 0 || y == total_lines - 1 || x == 0)
		return (1);
	if (matrix[y][x + 1] == '\0')
		return (1);
	if (x >= ft_strlen(matrix[y - 1]) || x >= ft_strlen(matrix[y + 1]))
		return (1);
	return (0);
}

static int	has_adjacent_space(char **matrix, int x, int y)
{
	if (matrix[y - 1][x] == ' ' || matrix[y + 1][x] == ' ' || matrix[y][x
		- 1] == ' ' || matrix[y][x + 1] == ' ')
		return (1);
	return (0);
}

void	check_map_matrix_closed(t_cube3d *cube3d)
{
	int		y;
	int		x;
	int		line_len;
	char	**matrix;

	y = 0;
	matrix = cube3d->map.matrix;
	while (y < cube3d->map.lines)
	{
		x = 0;
		line_len = ft_strlen(matrix[y]);
		while (x < line_len)
		{
			if (is_walkable(matrix[y][x]))
			{
				if (is_on_border(matrix, x, y, cube3d->map.lines))
					free_and_exit(cube3d, "Map is not closed");
				if (has_adjacent_space(matrix, x, y))
					free_and_exit(cube3d, "Map is not closed");
			}
			x++;
		}
		y++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evera <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 16:58:00 by evera             #+#    #+#             */
/*   Updated: 2026/08/26 16:58:04 by evera            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	calculate_lines(t_cube3d *cube3d)
{
	int		lines;
	char	*line;

	open_file(cube3d);
	lines = 0;
	line = get_next_line(cube3d->fd);
	while (line)
	{
		if (is_map(line))
			lines++;
		else if (!is_map(line) && lines > 0)
		{
			free(line);
			free_and_exit(cube3d, "Invalid map line");
		}
		free(line);
		line = get_next_line(cube3d->fd);
	}
	cube3d->map.lines = lines;
}

static void	set_matrix(t_cube3d *cube3d)
{
	int		i;
	int		started;
	char	*line;

	open_file(cube3d);
	i = 0;
	started = 0;
	line = get_next_line(cube3d->fd);
	while (line)
	{
		if (is_map(line) && i < cube3d->map.lines)
		{
			cube3d->map.matrix[i] = ft_strtrim(line, "\n");
			i++;
			started = 1;
		}
		else if (!is_map(line) && started == 1)
		{
			free(line);
			free_and_exit(cube3d, "Invalid map line");
		}
		free(line);
		line = get_next_line(cube3d->fd);
	}
}

static void	print_map(t_cube3d *cube3d)
{
	int	i;

	if (!cube3d || !cube3d->map.matrix)
		return ;
	i = 0;
	printf("--- START OF THE MAP ---\n");
	while (cube3d->map.matrix[i])
	{
		printf("%s\n", cube3d->map.matrix[i]);
		i++;
	}
	printf("--- END OF THE MAP (%d lines) ---\n", i);
}

void	init_map(t_cube3d *cube3d)
{
	calculate_lines(cube3d);
	cube3d->map.matrix = ft_calloc(cube3d->map.lines + 1, sizeof(char *));
	if (!cube3d->map.matrix)
		free_and_exit(cube3d, "Failed to initialize matrix");
	set_matrix(cube3d);
	print_map(cube3d);
}

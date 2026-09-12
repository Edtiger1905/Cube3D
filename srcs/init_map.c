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

static void	is_valid_player(t_cube3d *cube3d)
{
	int	i;
	int	has_player;

	i = 0;
	has_player = 0;
	while (i < cube3d->map.lines)
	{
		if (ft_strchr(cube3d->map.matrix[i], 'N')
			|| ft_strchr(cube3d->map.matrix[i], 'S')
			|| ft_strchr(cube3d->map.matrix[i], 'E')
			|| ft_strchr(cube3d->map.matrix[i], 'W'))
			has_player++;
		i++;
	}
	if (!has_player)
		free_and_exit(cube3d, "Missing player");
	if (has_player > 1)
		free_and_exit(cube3d, "There are too much players");
}

static void	set_player_position(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < map->lines)
	{
		if (ft_strchr(map->matrix[y], 'N') || ft_strchr(map->matrix[y], 'S')
			|| ft_strchr(map->matrix[y], 'E') || ft_strchr(map->matrix[y], 'W'))
		{
			while (map->matrix[y][x])
			{
				if (map->matrix[y][x] == 'N' || map->matrix[y][x] == 'S'
					|| map->matrix[y][x] == 'E' || map->matrix[y][x] == 'W')
					break ;
				x++;
			}
			break ;
		}
		y++;
	}
	map->player.x = x + 0.5;
	map->player.y = y + 0.5;
	map->player.dir = map->matrix[y][x];
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
	printf("Player position:\nx: %f\ny: %f\n", cube3d->map.player.x,
		cube3d->map.player.y);
	printf("Player direction: %c\n", cube3d->map.player.dir);
}

void	init_map(t_cube3d *cube3d)
{
	cube3d->map.player.x = -1;
	cube3d->map.player.y = -1;
	calculate_lines(cube3d);
	cube3d->map.matrix = ft_calloc(cube3d->map.lines + 1, sizeof(char *));
	if (!cube3d->map.matrix)
		free_and_exit(cube3d, "Failed to initialize matrix");
	set_matrix(cube3d);
	is_valid_player(cube3d);
	set_player_position(&cube3d->map);
	check_map_matrix_closed(cube3d);
	print_map(cube3d);
}

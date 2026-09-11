/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epandele <epandele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 12:00:00 by epandele          #+#    #+#             */
/*   Updated: 2026/09/11 17:30:22 by epandele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static int	cell_kind(t_cube3d *cube3d, int x, int y)
{
	char	c;

	if (y < 0 || y >= cube3d->map.lines || x < 0)
		return (0);
	if (x >= ft_strlen(cube3d->map.matrix[y]))
		return (0);
	c = cube3d->map.matrix[y][x];
	if (c == ' ')
		return (0);
	if (c == '1')
		return (2);
	return (1);
}

static void	push(t_stack *st, int x, int y)
{
	st->data[st->top].x = x;
	st->data[st->top].y = y;
	st->top++;
}

static int	flood_fill(t_cube3d *cube3d, char **visited, t_stack *st)
{
	t_pt	cur;
	int		kind;

	while (st->top > 0)
	{
		st->top--;
		cur = st->data[st->top];
		kind = cell_kind(cube3d, cur.x, cur.y);
		if (kind == 0)
			return (0);
		if (kind == 1 && !visited[cur.y][cur.x])
		{
			visited[cur.y][cur.x] = 1;
			push(st, cur.x + 1, cur.y);
			push(st, cur.x - 1, cur.y);
			push(st, cur.x, cur.y + 1);
			push(st, cur.x, cur.y - 1);
		}
	}
	return (1);
}

static char	**alloc_visited(t_cube3d *cube3d, int *out_max_w)
{
	char	**visited;
	int		i;
	int		max_w;

	max_w = 0;
	i = 0;
	while (i < cube3d->map.lines)
	{
		if (ft_strlen(cube3d->map.matrix[i]) > max_w)
			max_w = ft_strlen(cube3d->map.matrix[i]);
		i++;
	}
	*out_max_w = max_w;
	visited = malloc(sizeof(char *) * cube3d->map.lines);
	if (!visited)
		free_and_exit(cube3d, "Failed to allocate map check buffer");
	i = 0;
	while (i < cube3d->map.lines)
	{
		visited[i] = ft_calloc(max_w + 2, sizeof(char));
		if (!visited[i])
			free_and_exit(cube3d, "Failed to allocate map check buffer");
		i++;
	}
	return (visited);
}

void	check_map_closed(t_cube3d *cube3d)
{
	char	**visited;
	t_stack	st;
	int		max_w;
	int		ok;
	int		i;

	visited = alloc_visited(cube3d, &max_w);
	st.data = malloc(sizeof(t_pt) * (4 * cube3d->map.lines * max_w + 4));
	if (!st.data)
		free_and_exit(cube3d, "Failed to allocate map check stack");
	st.top = 0;
	push(&st, cube3d->map.player.x, cube3d->map.player.y);
	ok = flood_fill(cube3d, visited, &st);
	free(st.data);
	i = -1;
	while (++i < cube3d->map.lines)
		free(visited[i]);
	free(visited);
	if (!ok)
		free_and_exit(cube3d, "Map is not closed by walls");
}
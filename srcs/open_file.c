/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epandele <epandele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 12:00:00 by epandele          #+#    #+#             */
/*   Updated: 2026/09/12 12:00:00 by epandele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	is_cub_extension(char *src_map)
{
	char	*s;

	s = ft_strrchr(src_map, '.');
	if (!s || ft_strlen(s) > 4 || ft_strncmp(s, ".cub", 4) != 0)
		return (0);
	return (1);
}

void	open_file(t_cube3d *cube3d)
{
	if (cube3d->argc < 2)
		return (free_and_exit(cube3d, "Provide a map path"));
	if (cube3d->argc > 2)
		return (free_and_exit(cube3d, "Only map path is allowed"));
	cube3d->src_map = cube3d->argv[1];
	if (!is_cub_extension(cube3d->src_map))
		return (free_and_exit(cube3d, "Map must end with '.cub'"));
	if (cube3d->fd >= 0)
		flush_gnl(cube3d);
	cube3d->fd = open(cube3d->src_map, O_RDONLY);
	if (cube3d->fd < 0)
		return (free_and_exit(cube3d, "Cannot open the map file"));
}

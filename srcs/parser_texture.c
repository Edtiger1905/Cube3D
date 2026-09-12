/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evera <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 15:04:31 by evera             #+#    #+#             */
/*   Updated: 2026/08/26 15:04:33 by evera            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	set_texture(t_cube3d *cube3d, char **matrix, void **texture,
		t_texdim *dim)
{
	void	*img_ptr;

	if (*texture)
	{
		free_matrix(matrix);
		free_and_exit(cube3d, "Duplicate texture");
	}
	img_ptr = mlx_xpm_file_to_image(cube3d->mlx_ptr, matrix[1],
			&dim->w, &dim->h);
	if (!img_ptr)
	{
		free_matrix(matrix);
		free_and_exit(cube3d, "Failed load texture");
	}
	*texture = img_ptr;
}

static void	parser_matrix(t_cube3d *cube3d, char **matrix)
{
	char	*tmp;

	if (matrix_length(matrix) != 2)
	{
		free_matrix(matrix);
		free_and_exit(cube3d, "Expected: 'ID' <path_to_texture>");
	}
	if (ft_strlen(matrix[0]) != 2)
	{
		free_matrix(matrix);
		free_and_exit(cube3d, "Expected: 'NO', 'SO', 'EA', or 'WE'");
	}
	tmp = ft_strtrim(matrix[1], "\n");
	free(matrix[1]);
	matrix[1] = tmp;
}

void	parser_texture(t_cube3d *cube3d, char *line)
{
	char	**matrix;

	matrix = ft_split(line, ' ');
	free(line);
	parser_matrix(cube3d, matrix);
	if (ft_strncmp(matrix[0], "NO", 3) == 0)
		set_texture(cube3d, matrix, &cube3d->textures.north,
			&cube3d->textures.north_d);
	else if (ft_strncmp(matrix[0], "SO", 3) == 0)
		set_texture(cube3d, matrix, &cube3d->textures.south,
			&cube3d->textures.south_d);
	else if (ft_strncmp(matrix[0], "EA", 3) == 0)
		set_texture(cube3d, matrix, &cube3d->textures.east,
			&cube3d->textures.east_d);
	else if (ft_strncmp(matrix[0], "WE", 3) == 0)
		set_texture(cube3d, matrix, &cube3d->textures.west,
			&cube3d->textures.west_d);
	free_matrix(matrix);
}

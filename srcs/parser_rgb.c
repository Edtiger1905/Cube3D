/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_rgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evera <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 15:04:26 by evera             #+#    #+#             */
/*   Updated: 2026/08/26 15:04:27 by evera            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	is_valid_str_rgb(char *str_rgb)
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

static void	parser_matrix(t_cube3d *cube3d, char **matrix)
{
	char	*tmp;

	if (matrix_length(matrix) != 2)
	{
		free_matrix(matrix);
		free_and_exit(cube3d, "Expected: 'ID' <R,G,B>");
	}
	if (ft_strlen(matrix[0]) != 1)
	{
		free_matrix(matrix);
		free_and_exit(cube3d, "Expected: 'F' or 'C'");
	}
	tmp = ft_strtrim(matrix[1], "\n");
	free(matrix[1]);
	matrix[1] = tmp;
	if (!is_valid_str_rgb(matrix[1]))
	{
		free_matrix(matrix);
		free_and_exit(cube3d, "Expected: R,G,B");
	}
}

static void	convert_rgb(char **matrix_rgb, int *rgb)
{
	int	i;
	int	matrix_rgb_len;

	i = 0;
	matrix_rgb_len = matrix_length(matrix_rgb);
	while (i < matrix_rgb_len)
	{
		rgb[i] = ft_atoi(matrix_rgb[i]);
		i++;
	}
}

static void	set_rgb_texture(t_cube3d *cube3d, char **matrix, int *rgb)
{
	int	*texture;
	int	rgb_color;

	texture = NULL;
	if (!is_valid_rgb_number(rgb, 3))
	{
		free(rgb);
		free_matrix(matrix);
		free_and_exit(cube3d, "Number must be between 0 and 255");
	}
	rgb_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	if (ft_strncmp(matrix[0], "F", 1) == 0)
		texture = &cube3d->textures.floor;
	if (ft_strncmp(matrix[0], "C", 1) == 0)
		texture = &cube3d->textures.ceiling;
	if (!texture || *texture != -1)
	{
		free(rgb);
		free_matrix(matrix);
		free_and_exit(cube3d, "Duplicate RGB");
	}
	*texture = rgb_color;
}

void	parser_rgb(t_cube3d *cube3d, char *line)
{
	int		*rgb;
	char	**matrix;
	char	**matrix_rgb;

	rgb = malloc(sizeof(int) * 3);
	if (!rgb)
	{
		free(line);
		free_and_exit(cube3d, "Failed to initialize RGB");
	}
	matrix = ft_split(line, ' ');
	free(line);
	parser_matrix(cube3d, matrix);
	matrix_rgb = ft_split(matrix[1], ',');
	if (matrix_length(matrix_rgb) != 3)
	{
		free_matrix(matrix);
		free_matrix(matrix_rgb);
		free_and_exit(cube3d, "Expected: 'ID' <R,G,B>");
	}
	convert_rgb(matrix_rgb, rgb);
	free_matrix(matrix_rgb);
	set_rgb_texture(cube3d, matrix, rgb);
	free(rgb);
	free_matrix(matrix);
}

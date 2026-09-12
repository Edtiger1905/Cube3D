/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_rgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: epandele <epandele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 12:00:00 by epandele          #+#    #+#             */
/*   Updated: 2026/09/11 18:00:15 by epandele         ###   ########.fr       */
=======
/*   By: evera <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 15:04:26 by evera             #+#    #+#             */
/*   Updated: 2026/08/26 15:04:27 by evera            ###   ########.fr       */
>>>>>>> elvis
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

<<<<<<< HEAD
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
=======
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

static void	parser_matrix_rgb(t_cube3d *cube3d, char **matrix,
		char **matrix_rgb)
{
	if (matrix_length(matrix_rgb) != 3)
	{
		free_matrix(matrix);
		free_matrix(matrix_rgb);
		free_and_exit(cube3d, "Expected: 'ID' <R,G,B>");
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
>>>>>>> elvis
}

void	parser_rgb(t_cube3d *cube3d, char *line)
{
<<<<<<< HEAD
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
=======
	int		*rgb;
	char	**matrix;
	char	**matrix_rgb;

	matrix = ft_split(line, ' ');
	free(line);
	parser_matrix(cube3d, matrix);
	matrix_rgb = ft_split(matrix[1], ',');
	parser_matrix_rgb(cube3d, matrix, matrix_rgb);
	rgb = malloc(sizeof(int) * 3);
	if (!rgb)
	{
		free_matrix(matrix);
		free_matrix(matrix_rgb);
		free_and_exit(cube3d, "Failed to initialize RGB");
	}
	convert_rgb(matrix_rgb, rgb);
	free_matrix(matrix_rgb);
	set_rgb_texture(cube3d, matrix, rgb);
	free(rgb);
	free_matrix(matrix);
>>>>>>> elvis
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epandele <epandele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 13:55:45 by evera             #+#    #+#             */
/*   Updated: 2026/09/11 17:34:54 by epandele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	main(int argc, char **argv)
{
	t_cube3d	cube3d;

	cube3d.argc = argc;
	cube3d.argv = argv;
	init_cube3d(&cube3d);
	mlx_loop(cube3d.mlx_ptr);
	free_cube3d(&cube3d);
}
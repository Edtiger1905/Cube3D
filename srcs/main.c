/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evera <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 13:55:45 by evera             #+#    #+#             */
/*   Updated: 2026/08/26 13:55:47 by evera            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	main(int argc, char **argv)
{
	t_cube3d	cube3d;

	cube3d.argc = argc;
	cube3d.argv = argv;
	init_cube3d(&cube3d);
	free_cube3d(&cube3d);
}

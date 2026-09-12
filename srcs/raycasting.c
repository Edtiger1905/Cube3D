/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epandele <epandele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 12:00:00 by epandele          #+#    #+#             */
/*   Updated: 2026/09/11 12:00:00 by epandele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	init_ray(t_cube3d *cube3d, t_ray *ray, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->ray_dir_x = cube3d->cam.dir_x + cube3d->cam.plane_x * camera_x;
	ray->ray_dir_y = cube3d->cam.dir_y + cube3d->cam.plane_y * camera_x;
	ray->map_x = (int)cube3d->cam.pos_x;
	ray->map_y = (int)cube3d->cam.pos_y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

static void	init_step_and_side_dist(t_cube3d *cube3d, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (cube3d->cam.pos_x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - cube3d->cam.pos_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (cube3d->cam.pos_y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - cube3d->cam.pos_y)
			* ray->delta_dist_y;
	}
}

static void	perform_dda(t_cube3d *cube3d, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		hit = is_wall(cube3d, ray->map_x, ray->map_y);
	}
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	if (ray->perp_wall_dist < 0.0001)
		ray->perp_wall_dist = 0.0001;
}

int	render_frame(void *param)
{
	t_cube3d	*cube3d;
	t_ray		ray;
	int			x;

	cube3d = (t_cube3d *)param;
	update_movement(cube3d);
	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(cube3d, &ray, x);
		init_step_and_side_dist(cube3d, &ray);
		perform_dda(cube3d, &ray);
		draw_column(cube3d, &ray, x);
		x++;
	}
	mlx_put_image_to_window(cube3d->mlx_ptr, cube3d->win_ptr,
		cube3d->screen.img, 0, 0);
	return (0);
}

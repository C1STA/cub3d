/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_calc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 23:59:30 by dpinto            #+#    #+#             */
/*   Updated: 2025/07/11 00:03:45 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	calculate_perp_wall_dist(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x == 0)
			ray->perp_wall_dist = 1.0;
		else
			ray->perp_wall_dist = (ray->map_x - ray->pos_x + (1 - ray->step_x)
					/ 2) / ray->ray_dir_x;
	}
	else
	{
		if (ray->ray_dir_y == 0)
			ray->perp_wall_dist = 1.0;
		else
			ray->perp_wall_dist = (ray->map_y - ray->pos_y + (1 - ray->step_y)
					/ 2) / ray->ray_dir_y;
	}
	if (ray->perp_wall_dist <= 0.01)
		ray->perp_wall_dist = 0.01;
}

void	calculate_wall_height(t_ray *ray)
{
	calculate_perp_wall_dist(ray);
	ray->line_height = (int)(WINDOW_HEIGHT / ray->perp_wall_dist);
	if (ray->line_height > WINDOW_HEIGHT * 10)
		ray->line_height = WINDOW_HEIGHT * 10;
	ray->draw_start = -ray->line_height / 2 + WINDOW_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WINDOW_HEIGHT / 2;
	if (ray->draw_end >= WINDOW_HEIGHT)
		ray->draw_end = WINDOW_HEIGHT - 1;
}

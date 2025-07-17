/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:42:45 by dpinto            #+#    #+#             */
/*   Updated: 2025/07/17 22:24:41 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	init_ray_ns(t_ray *ray, char dir)
{
	if (dir == 'N')
	{
		ray->dir_x = 0;
		ray->dir_y = -1;
		ray->plane_x = 0.66;
		ray->plane_y = 0;
	}
	else if (dir == 'S')
	{
		ray->dir_x = 0;
		ray->dir_y = 1;
		ray->plane_x = -0.66;
		ray->plane_y = 0;
	}
}

static void	init_ray_ew(t_ray *ray, char dir)
{
	if (dir == 'E')
	{
		ray->dir_x = 1;
		ray->dir_y = 0;
		ray->plane_x = 0;
		ray->plane_y = 0.66;
	}
	else if (dir == 'W')
	{
		ray->dir_x = -1;
		ray->dir_y = 0;
		ray->plane_x = 0;
		ray->plane_y = -0.66;
	}
}

void	init_ray_values(t_ray *ray, t_fields *fields)
{
	ray->pos_x = fields->map->player_x + 0.5;
	ray->pos_y = fields->map->player_y + 0.5;
	if (fields->map->player_dir == 'N' || fields->map->player_dir == 'S')
		init_ray_ns(ray, fields->map->player_dir);
	else
		init_ray_ew(ray, fields->map->player_dir);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 02:10:45 by dpinto            #+#    #+#             */
/*   Updated: 2025/05/28 02:22:45 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <math.h>

#define MOVE_SPEED 0.08
#define ROT_SPEED 0.05
#define WALL_MARGIN 0.3

void	rotate_player(t_ray *ray, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = ray->dir_x;
	ray->dir_x = ray->dir_x * cos(rot_speed) - ray->dir_y * sin(rot_speed);
	ray->dir_y = old_dir_x * sin(rot_speed) + ray->dir_y * cos(rot_speed);
	old_plane_x = ray->plane_x;
	ray->plane_x = ray->plane_x * cos(rot_speed) - ray->plane_y
		* sin(rot_speed);
	ray->plane_y = old_plane_x * sin(rot_speed) + ray->plane_y * cos(rot_speed);
}

static int	check_bounds(t_fields *fields, double next_x, double next_y)
{
	return (next_x < 0 || next_y < 0 || next_x >= fields->map->width
		|| next_y >= fields->map->height);
}

static int	check_wall_collision(t_fields *fields, double next_x, double next_y)
{
	return (fields->map->grid[(int)next_y][(int)next_x] == '1'
		|| fields->map->grid[(int)(next_y + WALL_MARGIN)][(int)next_x] == '1'
		|| fields->map->grid[(int)(next_y - WALL_MARGIN)][(int)next_x] == '1'
		|| fields->map->grid[(int)next_y][(int)(next_x + WALL_MARGIN)] == '1'
		|| fields->map->grid[(int)next_y][(int)(next_x - WALL_MARGIN)] == '1');
}

int	check_collision(t_fields *fields, double next_x, double next_y)
{
	if (check_bounds(fields, next_x, next_y))
		return (1);
	if (check_wall_collision(fields, next_x, next_y))
		return (1);
	return (0);
}

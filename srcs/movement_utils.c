/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 02:10:45 by dpinto            #+#    #+#             */
/*   Updated: 2025/07/10 23:43:08 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <math.h>

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

static int	is_wall_at_position(t_fields *fields, double x, double y)
{
	int	check_x;
	int	check_y;

	check_x = (int)x;
	check_y = (int)y;
	if (check_x >= 0 && check_x < fields->map->width && check_y >= 0
		&& check_y < fields->map->height
		&& fields->map->grid[check_y][check_x] == '1')
		return (1);
	return (0);
}

static int	check_wall_collision(t_fields *fields, double next_x, double next_y)
{
	if (is_wall_at_position(fields, next_x, next_y))
		return (1);
	if (is_wall_at_position(fields, next_x, next_y + WALL_MARGIN))
		return (1);
	if (is_wall_at_position(fields, next_x, next_y - WALL_MARGIN))
		return (1);
	if (is_wall_at_position(fields, next_x + WALL_MARGIN, next_y))
		return (1);
	if (is_wall_at_position(fields, next_x - WALL_MARGIN, next_y))
		return (1);
	return (0);
}

int	check_collision(t_fields *fields, double next_x, double next_y)
{
	if (check_bounds(fields, next_x, next_y))
		return (1);
	if (check_wall_collision(fields, next_x, next_y))
		return (1);
	return (0);
}

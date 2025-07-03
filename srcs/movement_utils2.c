/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 02:10:45 by dpinto            #+#    #+#             */
/*   Updated: 2025/05/29 05:49:55 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	move_player(t_fields *fields, t_ray *ray, double dir_x, double dir_y)
{
	double	next_x;
	double	next_y;

	next_x = ray->pos_x + dir_x * MOVE_SPEED;
	next_y = ray->pos_y + dir_y * MOVE_SPEED;
	if (!check_collision(fields, next_x + dir_x * WALL_MARGIN, ray->pos_y))
	{
		ray->pos_x = next_x;
		fields->map->player_x = (int)ray->pos_x;
	}
	if (!check_collision(fields, ray->pos_x, next_y + dir_y * WALL_MARGIN))
	{
		ray->pos_y = next_y;
		fields->map->player_y = (int)ray->pos_y;
	}
}

int	handle_wasd(int keycode, t_fields *fields)
{
	if (keycode == XK_w)
	{
		move_player(fields, fields->ray, fields->ray->dir_x,
			fields->ray->dir_y);
		return (1);
	}
	else if (keycode == XK_s)
	{
		move_player(fields, fields->ray, -fields->ray->dir_x,
			-fields->ray->dir_y);
		return (1);
	}
	else if (keycode == XK_a)
	{
		move_player(fields, fields->ray, fields->ray->dir_y,
			-fields->ray->dir_x);
		return (1);
	}
	else if (keycode == XK_d)
	{
		move_player(fields, fields->ray, -fields->ray->dir_y,
			fields->ray->dir_x);
		return (1);
	}
	return (0);
}

int	handle_rotation(int keycode, t_fields *fields)
{
	if (keycode == XK_Left)
	{
		rotate_player(fields->ray, -ROT_SPEED);
		return (1);
	}
	else if (keycode == XK_Right)
	{
		rotate_player(fields->ray, ROT_SPEED);
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:42:45 by dpinto            #+#    #+#             */
/*   Updated: 2025/06/02 03:19:06 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void		init_ray_values(t_ray *ray, t_fields *fields);
int			load_textures(t_fields *fields);

static int	handle_close(t_fields *fields)
{
	mlx_loop_end(fields->mlx);
	return (0);
}

static int	handle_keypress(int keycode, t_fields *fields)
{
	if (keycode == XK_Escape)
		mlx_loop_end(fields->mlx);
	else
		handle_movement(keycode, fields);
	return (0);
}

static int	init_mlx_resources(t_fields *fields)
{
	fields->mlx = mlx_init();
	if (!fields->mlx)
		return (1);
	if (load_textures(fields))
	{
		ft_putstr_fd("Error loading textures\n", 2);
		return (1);
	}
	fields->win = mlx_new_window(fields->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"Cub3D");
	if (!fields->win)
		return (1);
	return (0);
}

int	init_window(t_fields *fields)
{
	if (init_mlx_resources(fields))
		return (1);
	fields->ray = malloc(sizeof(t_ray));
	if (!fields->ray)
		return (1);
	init_ray_values(fields->ray, fields);
	cast_rays(fields, fields->ray);
	mlx_hook(fields->win, DestroyNotify, 0, handle_close, fields);
	mlx_hook(fields->win, KeyPress, KeyPressMask, handle_keypress, fields);
	mlx_loop(fields->mlx);
	return (0);
}

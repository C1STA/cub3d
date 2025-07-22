/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:42:45 by dpinto            #+#    #+#             */
/*   Updated: 2025/07/18 06:32:28 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void		init_ray_values(t_ray *ray, t_fields *fields);
int			load_textures(t_fields *fields);

static int	init_mlx_resources(t_fields *fields)
{
	int	window_width;
	int	window_height;

	fields->mlx = mlx_init();
	if (!fields->mlx)
		return (1);
	window_width = WINDOW_WIDTH;
	window_height = WINDOW_HEIGHT;
	if (window_width <= 0 || window_width > 1920)
		return (ft_putstr_fd("Error\nInvalid resolution\n", 2), 1);
	if (window_height <= 0 || window_height > 1080)
		return (ft_putstr_fd("Error\nInvalid resolution\n", 2), 1);
	if (limit_window_size(fields->mlx, &window_width, &window_height))
		return (1);
	if (load_textures(fields))
	{
		ft_putstr_fd("Error\nUnable to load texture(s)\n", 2);
		return (1);
	}
	fields->win = mlx_new_window(fields->mlx, window_width, window_height,
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

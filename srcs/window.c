/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:42:45 by dpinto            #+#    #+#             */
/*   Updated: 2025/05/26 02:56:27 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static int	handle_close(t_fields *fields)
{
	mlx_loop_end(fields->mlx);
	return (0);
}

static int	handle_keypress(int keycode, t_fields *fields)
{
	if (keycode == XK_Escape)
		mlx_loop_end(fields->mlx);
	return (0);
}

static int	init_mlx_window(t_fields *fields)
{
	fields->mlx = mlx_init();
	if (!fields->mlx)
	{
		ft_putstr_fd("Error\nMLX initialization failed\n", 2);
		return (1);
	}
	fields->win = mlx_new_window(fields->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"Cub3D");
	if (!fields->win)
	{
		ft_putstr_fd("Error\nWindow creation failed\n", 2);
		mlx_destroy_display(fields->mlx);
		free(fields->mlx);
		return (1);
	}
	return (0);
}

static int	load_texture(t_fields *fields)
{
	fields->texture = mlx_xpm_file_to_image(fields->mlx, fields->no_filename,
			&fields->tex_width, &fields->tex_height);
	if (!fields->texture)
	{
		ft_putstr_fd("Error\nFailed to load texture\n", 2);
		return (1);
	}
	return (0);
}

int	init_window(t_fields *fields)
{
	if (init_mlx_window(fields))
		return (1);
	if (load_texture(fields))
	{
		mlx_destroy_window(fields->mlx, fields->win);
		mlx_destroy_display(fields->mlx);
		free(fields->mlx);
		return (1);
	}
	mlx_put_image_to_window(fields->mlx, fields->win, fields->texture, 0, 0);
	mlx_hook(fields->win, DestroyNotify, 0, handle_close, fields);
	mlx_hook(fields->win, KeyPress, KeyPressMask, handle_keypress, fields);
	return (0);
}
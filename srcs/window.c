/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:42:45 by dpinto            #+#    #+#             */
/*   Updated: 2025/05/26 03:53:32 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"
#include <math.h>

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

static int	load_textures(t_fields *fields)
{
	fields->no_texture = mlx_xpm_file_to_image(fields->mlx, fields->no_filename,
			&fields->tex_width, &fields->tex_height);
	fields->so_texture = mlx_xpm_file_to_image(fields->mlx, fields->so_filename,
			&fields->tex_width, &fields->tex_height);
	fields->we_texture = mlx_xpm_file_to_image(fields->mlx, fields->we_filename,
			&fields->tex_width, &fields->tex_height);
	fields->ea_texture = mlx_xpm_file_to_image(fields->mlx, fields->ea_filename,
			&fields->tex_width, &fields->tex_height);
	if (!fields->no_texture || !fields->so_texture || !fields->we_texture
		|| !fields->ea_texture)
		return (1);
	return (0);
}

static void	init_ray_values(t_ray *ray, t_fields *fields)
{
	ray->pos_x = fields->map->player_x;
	ray->pos_y = fields->map->player_y;
	if (fields->map->player_dir == 'N')
	{
		ray->dir_x = 0;
		ray->dir_y = -1;
		ray->plane_x = 0.66;
		ray->plane_y = 0;
	}
	else if (fields->map->player_dir == 'S')
	{
		ray->dir_x = 0;
		ray->dir_y = 1;
		ray->plane_x = -0.66;
		ray->plane_y = 0;
	}
	else if (fields->map->player_dir == 'E')
	{
		ray->dir_x = 1;
		ray->dir_y = 0;
		ray->plane_x = 0;
		ray->plane_y = 0.66;
	}
	else if (fields->map->player_dir == 'W')
	{
		ray->dir_x = -1;
		ray->dir_y = 0;
		ray->plane_x = 0;
		ray->plane_y = -0.66;
	}
}

int	init_window(t_fields *fields)
{
	fields->mlx = mlx_init();
	if (!fields->mlx)
		return (1);
	fields->win = mlx_new_window(fields->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"Cub3D");
	if (!fields->win)
	{
		mlx_destroy_display(fields->mlx);
		free(fields->mlx);
		return (1);
	}
	if (load_textures(fields))
	{
		mlx_destroy_window(fields->mlx, fields->win);
		mlx_destroy_display(fields->mlx);
		free(fields->mlx);
		return (1);
	}
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
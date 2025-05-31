/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:42:45 by dpinto            #+#    #+#             */
/*   Updated: 2025/05/31 05:44:14 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void		init_ray_values(t_ray *ray, t_fields *fields);

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

static void	cleanup_loaded_textures(t_fields *fields)
{
	if (fields->no_texture)
		mlx_destroy_image(fields->mlx, fields->no_texture);
	if (fields->so_texture)
		mlx_destroy_image(fields->mlx, fields->so_texture);
	if (fields->we_texture)
		mlx_destroy_image(fields->mlx, fields->we_texture);
	if (fields->ea_texture)
		mlx_destroy_image(fields->mlx, fields->ea_texture);
	fields->no_texture = NULL;
	fields->so_texture = NULL;
	fields->we_texture = NULL;
	fields->ea_texture = NULL;
}

static void	*load_single_texture(t_fields *fields, char *filename)
{
	void	*texture;

	texture = mlx_xpm_file_to_image(fields->mlx, filename, &fields->tex_width,
			&fields->tex_height);
	if (!texture)
		cleanup_loaded_textures(fields);
	return (texture);
}

static int	load_textures(t_fields *fields)
{
	fields->no_texture = load_single_texture(fields, fields->no_filename);
	if (!fields->no_texture)
		return (1);
	fields->so_texture = load_single_texture(fields, fields->so_filename);
	if (!fields->so_texture)
		return (1);
	fields->we_texture = load_single_texture(fields, fields->we_filename);
	if (!fields->we_texture)
		return (1);
	fields->ea_texture = load_single_texture(fields, fields->ea_filename);
	if (!fields->ea_texture)
		return (1);
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

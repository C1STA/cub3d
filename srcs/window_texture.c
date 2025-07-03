/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:42:45 by dpinto            #+#    #+#             */
/*   Updated: 2025/06/02 03:19:09 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	cleanup_loaded_textures(t_fields *fields)
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

int	load_textures(t_fields *fields)
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

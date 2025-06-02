/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:42:45 by dpinto            #+#    #+#             */
/*   Updated: 2025/06/02 02:20:58 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

size_t	get_tab_len(char **tab)
{
	size_t	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}

char	**free_strs(char **strs)
{
	size_t	i;

	i = 0;
	while (strs && strs[i])
	{
		free(strs[i]);
		i++;
	}
	if (strs)
		free(strs);
	return (NULL);
}

void	init_fields(t_fields *fields)
{
	fields->no_filename = NULL;
	fields->so_filename = NULL;
	fields->we_filename = NULL;
	fields->ea_filename = NULL;
	fields->floor[0] = -1;
	fields->floor[1] = -1;
	fields->floor[2] = -1;
	fields->core[0] = -1;
	fields->core[1] = -1;
	fields->core[2] = -1;
	fields->map = NULL;
	fields->mlx = NULL;
	fields->win = NULL;
	fields->no_texture = NULL;
	fields->so_texture = NULL;
	fields->we_texture = NULL;
	fields->ea_texture = NULL;
	fields->ray = NULL;
}

static void	free_mlx_resources(t_fields *fields)
{
	if (fields->win)
	{
		mlx_destroy_window(fields->mlx, fields->win);
		fields->win = NULL;
	}
	if (fields->no_texture)
	{
		mlx_destroy_image(fields->mlx, fields->no_texture);
		fields->no_texture = NULL;
	}
	if (fields->so_texture)
	{
		mlx_destroy_image(fields->mlx, fields->so_texture);
		fields->so_texture = NULL;
	}
	if (fields->we_texture)
	{
		mlx_destroy_image(fields->mlx, fields->we_texture);
		fields->we_texture = NULL;
	}
	if (fields->ea_texture)
	{
		mlx_destroy_image(fields->mlx, fields->ea_texture);
		fields->ea_texture = NULL;
	}
	if (fields->mlx)
	{
		mlx_destroy_display(fields->mlx);
		free(fields->mlx);
		fields->mlx = NULL;
	}
}

void	free_fields(t_fields *fields)
{
	free_mlx_resources(fields);
	if (fields->ray)
		free(fields->ray);
	if (fields->no_filename)
		free(fields->no_filename);
	if (fields->so_filename)
		free(fields->so_filename);
	if (fields->we_filename)
		free(fields->we_filename);
	if (fields->ea_filename)
		free(fields->ea_filename);
	if (fields->map)
	{
		if (fields->map->grid)
			free_strs(fields->map->grid);
		free(fields->map);
	}
}

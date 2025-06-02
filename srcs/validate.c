/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:42:45 by dpinto            #+#    #+#             */
/*   Updated: 2025/05/31 05:51:33 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	validate_colors(t_fields *fields)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (fields->floor[i] < 0 || fields->floor[i] > 255)
			return (1);
		if (fields->core[i] < 0 || fields->core[i] > 255)
			return (1);
		i++;
	}
	return (0);
}

int	validate_textures(t_fields *fields)
{
	int	fd;

	fd = open(fields->no_filename, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	fd = open(fields->so_filename, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	fd = open(fields->we_filename, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	fd = open(fields->ea_filename, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	return (0);
}

static int	check_map_row(t_map *map, int i)
{
	int	j;

	j = 0;
	while (j < map->width)
	{
		if (check_walls(map, i, j))
		{
			ft_putstr_fd("Error\nMap not properly closed\n", 2);
			return (1);
		}
		j++;
	}
	return (0);
}

int	validate_map(t_map *map)
{
	int	i;

	if (check_map_chars(map))
	{
		ft_putstr_fd("Error\nInvalid characters in map\n", 2);
		return (1);
	}
	i = 0;
	while (i < map->height)
	{
		if (check_map_row(map, i))
			return (1);
		i++;
	}
	return (0);
}

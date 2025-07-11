/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_validation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 03:10:00 by dpinto            #+#    #+#             */
/*   Updated: 2025/07/12 01:01:49 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	process_line_dimension(char *line, int *height, int *max_width,
		int *map_started)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && !is_empty_line(line))
	{
		if (len > *max_width)
			*max_width = len;
		(*height)++;
		*map_started = 1;
	}
	else if (*map_started && (len == 0 || is_empty_line(line)))
	{
		ft_putstr_fd("Error\nEmpty line inside map\n", 2);
		return (1);
	}
	return (0);
}

static int	calculate_map_dimensions(char **tab, int map_start, int *height,
		int *max_width)
{
	int	i;
	int	map_started;

	*height = 0;
	*max_width = 0;
	map_started = 0;
	i = map_start;
	while (tab[i])
	{
		if (process_line_dimension(tab[i], height, max_width, &map_started))
			return (1);
		i++;
	}
	return (0);
}

static int	allocate_map_memory(t_fields *fields, int height)
{
	fields->map = malloc(sizeof(t_map));
	if (!fields->map)
		return (1);
	fields->map->grid = malloc(sizeof(char *) * (height + 1));
	if (!fields->map->grid)
		return (1);
	return (0);
}

static int	fill_map_grid(char **tab, int map_start, t_fields *fields,
		int max_width)
{
	char	*padded;
	int		i;
	int		j;
	int		len;

	i = map_start;
	j = 0;
	while (tab[i])
	{
		len = ft_strlen(tab[i]);
		if (len > 0 && !is_empty_line(tab[i]))
		{
			padded = malloc(max_width + 1);
			if (!padded)
				return (1);
			ft_memset(padded, ' ', max_width);
			ft_memcpy(padded, tab[i], len);
			padded[max_width] = '\0';
			fields->map->grid[j] = padded;
			j++;
		}
		i++;
	}
	fields->map->grid[j] = NULL;
	return (0);
}

int	fill_map_from_lines(char **tab, int map_start, t_fields *fields)
{
	int	height;
	int	max_width;

	if (calculate_map_dimensions(tab, map_start, &height, &max_width))
		return (1);
	if (height == 0)
		return (1);
	if (allocate_map_memory(fields, height))
		return (1);
	if (fill_map_grid(tab, map_start, fields, max_width))
		return (1);
	fields->map->height = height;
	fields->map->width = max_width;
	return (0);
}

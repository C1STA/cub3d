/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:42:45 by dpinto            #+#    #+#             */
/*   Updated: 2025/06/02 03:19:11 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	get_map_dimensions(char **tab, int start, t_map *map)
{
	int	i;
	int	len;
	int	j;

	map->width = 0;
	map->height = 0;
	i = start;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j] && tab[i][j] == ' ')
			j++;
		len = ft_strlen(tab[i] + j);
		if (len > map->width)
			map->width = len;
		map->height++;
		i++;
	}
	return (0);
}

char	*pad_line(char *line, int width)
{
	char	*padded;
	int		i;
	int		len;

	padded = malloc(sizeof(char) * (width + 1));
	if (!padded)
		return (NULL);
	len = ft_strlen(line);
	i = 0;
	while (i < len && i < width)
	{
		padded[i] = line[i];
		i++;
	}
	while (i < width)
	{
		padded[i] = ' ';
		i++;
	}
	padded[i] = '\0';
	return (padded);
}

static int	process_map_line(t_map *map, char **tab, int start, int i)
{
	char	*padded;

	padded = pad_line(tab[start + i], map->width);
	if (!padded)
		return (1);
	map->grid[i] = padded;
	return (0);
}

int	copy_map(char **tab, int start, t_map *map)
{
	int	i;

	map->grid = malloc(sizeof(char *) * (map->height + 1));
	if (!map->grid)
		return (1);
	i = 0;
	while (i < map->height)
	{
		if (process_map_line(map, tab, start, i))
			return (1);
		i++;
	}
	map->grid[i] = NULL;
	return (0);
}

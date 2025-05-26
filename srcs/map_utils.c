/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:42:45 by dpinto            #+#    #+#             */
/*   Updated: 2025/05/26 02:57:07 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

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

static void	print_map_info(t_map *map, char *line, char *padded)
{
	if (line)
	{
		ft_putstr_fd("Original line: ", 1);
		ft_putstr_fd(line, 1);
		ft_putstr_fd("\n", 1);
	}
	else
	{
		ft_putstr_fd("Copying map with dimensions: ", 1);
		ft_putnbr_fd(map->width, 1);
		ft_putstr_fd("x", 1);
		ft_putnbr_fd(map->height, 1);
		ft_putstr_fd("\n", 1);
	}
	if (padded)
	{
		ft_putstr_fd("Padded line: ", 1);
		ft_putstr_fd(padded, 1);
		ft_putstr_fd("\n", 1);
	}
}

static int	process_map_line(t_map *map, char **tab, int start, int i)
{
	char	*padded;

	print_map_info(map, tab[start + i], NULL);
	padded = pad_line(tab[start + i], map->width);
	if (!padded)
	{
		free_strs(map->grid);
		return (1);
	}
	map->grid[i] = padded;
	print_map_info(map, NULL, padded);
	return (0);
}

int	copy_map(char **tab, int start, t_map *map)
{
	int i;

	print_map_info(map, NULL, NULL);
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
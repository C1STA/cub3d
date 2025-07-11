/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_validation2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 01:00:00 by dpinto            #+#    #+#             */
/*   Updated: 2025/07/12 01:13:47 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	process_player_character(t_map *map, int i, int j, int *found)
{
	if (*found)
	{
		ft_putstr_fd("Error\nMultiple player positions\n", 2);
		return (1);
	}
	map->player_x = j;
	map->player_y = i;
	map->player_dir = map->grid[i][j];
	map->grid[i][j] = '0';
	*found = 1;
	return (0);
}

int	find_player_in_map(t_map *map)
{
	int	i;
	int	j;
	int	found;

	found = 0;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (map->grid[i][j] == 'N' || map->grid[i][j] == 'S'
				|| map->grid[i][j] == 'E' || map->grid[i][j] == 'W')
				if (process_player_character(map, i, j, &found))
					return (1);
			j++;
		}
		i++;
	}
	if (!found)
	{
		ft_putstr_fd("Error\nNo player position\n", 2);
		return (1);
	}
	return (0);
}

static int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ');
}

int	validate_map_structure(t_map *map)
{
	if (!map || !map->grid || map->height <= 0 || map->width <= 0)
	{
		ft_putstr_fd("Error\nMap structure invalid\n", 2);
		return (1);
	}
	return (0);
}

int	validate_character_at_position(t_map *map, int i, int j, char c)
{
	int	w;

	w = map->width;
	if (!is_valid_map_char(c))
	{
		ft_putstr_fd("Error\nInvalid character in map\n", 2);
		return (1);
	}
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (i == 0 || j == 0 || i == map->height - 1 || j == w - 1)
		{
			ft_putstr_fd("Error\nMap not closed\n", 2);
			return (1);
		}
		if (map->grid[i - 1][j] == ' ' || map->grid[i + 1][j] == ' '
			|| map->grid[i][j - 1] == ' ' || map->grid[i][j + 1] == ' ')
		{
			ft_putstr_fd("Error\nMap not closed\n", 2);
			return (1);
		}
	}
	return (0);
}

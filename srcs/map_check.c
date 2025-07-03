/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:42:45 by dpinto            #+#    #+#             */
/*   Updated: 2025/05/26 02:27:58 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	check_player_count(int player_count)
{
	if (player_count != 1)
	{
		ft_putstr_fd("Error\nInvalid number of players: ", 2);
		ft_putnbr_fd(player_count, 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	return (0);
}

static int	process_map_char(t_map *map, int i, int j, int *player_count)
{
	if (!ft_strchr(MAP_CHARS, map->grid[i][j]))
	{
		ft_putstr_fd("Error\nInvalid character: ", 2);
		write(2, &map->grid[i][j], 1);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	if (ft_strchr(VALID_PLAYER, map->grid[i][j]))
	{
		(*player_count)++;
		map->player_x = j;
		map->player_y = i;
		map->player_dir = map->grid[i][j];
	}
	return (0);
}

int	check_map_chars(t_map *map)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (process_map_char(map, i, j, &player_count))
				return (1);
			j++;
		}
		i++;
	}
	return (check_player_count(player_count));
}

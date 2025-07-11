/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_validation3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 01:10:00 by dpinto            #+#    #+#             */
/*   Updated: 2025/07/12 01:02:54 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	check_player_position(t_map *map)
{
	if (map->player_x < 0 || map->player_x >= map->width || map->player_y < 0
		|| map->player_y >= map->height)
	{
		ft_putstr_fd("Error\nPlayer position out of map bounds\n", 2);
		return (1);
	}
	return (0);
}

int	parse_validate_map(t_map *map)
{
	char	c;
	int		i;
	int		j;
	int		w;

	if (validate_map_structure(map))
		return (1);
	i = 0;
	while (i < map->height)
	{
		w = map->width;
		j = 0;
		while (j < w)
		{
			c = map->grid[i][j];
			if (validate_character_at_position(map, i, j, c))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

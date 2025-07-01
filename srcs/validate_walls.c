/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_walls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:42:45 by dpinto            #+#    #+#             */
/*   Updated: 2025/05/28 05:13:32 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static int	check_border_walls(t_map *map, int i, int j)
{
	if (map->grid[i][j] != '1' && map->grid[i][j] != ' ')
	{
		ft_putstr_fd("Error\nMap border not closed at ", 2);
		ft_putnbr_fd(i, 2);
		ft_putstr_fd(",", 2);
		ft_putnbr_fd(j, 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	return (0);
}

static int	check_inner_walls(t_map *map, int i, int j)
{
	if (map->grid[i][j] == '0' || ft_strchr(VALID_PLAYER, map->grid[i][j]))
	{
		if (i > 0 && map->grid[i - 1][j] == ' ')
			return (1);
		if (i < map->height - 1 && map->grid[i + 1][j] == ' ')
			return (1);
		if (j > 0 && map->grid[i][j - 1] == ' ')
			return (1);
		if (j < map->width - 1 && map->grid[i][j + 1] == ' ')
			return (1);
	}
	return (0);
}

int	check_walls(t_map *map, int i, int j)
{
	if (i == 0 || i == map->height - 1 || j == 0 || j == map->width - 1)
		return (check_border_walls(map, i, j));
	return (check_inner_walls(map, i, j));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_fields.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:42:45 by dpinto            #+#    #+#             */
/*   Updated: 2025/05/26 01:47:37 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void	print_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		printf("%s\n", map->grid[i]);
		i++;
	}
	printf("\n=========================\n");
}

void	print_fields(t_fields *fields)
{
	printf("NO: %s\n", fields->no_filename);
	printf("SO: %s\n", fields->so_filename);
	printf("WE: %s\n", fields->we_filename);
	printf("EA: %s\n", fields->ea_filename);
	printf("F: %d,%d,%d\n", fields->floor[0], fields->floor[1],
		fields->floor[2]);
	printf("C: %d,%d,%d\n", fields->core[0], fields->core[1], fields->core[2]);
	if (fields->map)
		print_map(fields->map);
}
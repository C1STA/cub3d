/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:42:45 by dpinto            #+#    #+#             */
/*   Updated: 2025/05/28 05:38:28 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	parse_map(char **tab, int start_idx, t_fields *fields)
{
	fields->map = malloc(sizeof(t_map));
	if (!fields->map)
		return (1);
	if (get_map_dimensions(tab, start_idx, fields->map))
		return (1);
	if (copy_map(tab, start_idx, fields->map))
		return (1);
	if (check_map_chars(fields->map))
		return (1);
	if (validate_map(fields->map))
		return (1);
	return (0);
}

int	find_map_start(char **tab)
{
	int	i;
	int	fields_found;
	int	result;

	i = 0;
	fields_found = 0;
	while (tab[i])
	{
		if (ft_strlen(tab[i]) > 0)
		{
			result = check_map_line(tab[i], fields_found);
			if (result == 1)
				return (i);
			else if (result == -1)
				return (-1);
			else if (result == 2)
				fields_found++;
		}
		i++;
	}
	return (-1);
}

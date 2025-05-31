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

#include "../includes/cube3d.h"

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

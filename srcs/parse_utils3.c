/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 01:20:00 by dpinto            #+#    #+#             */
/*   Updated: 2025/07/16 04:13:53 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	is_line_empty(char *line_start, char *line_end)
{
	char	*check_ptr;

	check_ptr = line_start;
	while (check_ptr < line_end)
	{
		if (*check_ptr != ' ' && *check_ptr != '\t')
			return (0);
		check_ptr++;
	}
	return (1);
}

int	validate_map_content(char *map_start_ptr, char *last_valid_line)
{
	char	*line_start;
	char	*end_ptr;

	line_start = map_start_ptr;
	end_ptr = map_start_ptr;
	while (*end_ptr)
		end_ptr++;
	while (map_start_ptr < end_ptr)
	{
		if (*map_start_ptr == '\n')
		{
			if (is_line_empty(line_start, map_start_ptr))
			{
				ft_putstr_fd("Error\nEmpty line inside map\n", 2);
				return (1);
			}
			map_start_ptr++;
			line_start = map_start_ptr;
		}
		else
			map_start_ptr++;
	}
	return (0);
}

int	check_empty_lines_in_map(char *file_content)
{
	char	*map_start_ptr;
	char	*last_valid_line;

	map_start_ptr = find_map_start_ptr(file_content);
	if (!map_start_ptr)
		return (0);
	last_valid_line = find_last_valid_line(map_start_ptr);
	return (validate_map_content(map_start_ptr, last_valid_line));
}

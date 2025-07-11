/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 00:45:00 by dpinto            #+#    #+#             */
/*   Updated: 2025/07/12 01:13:24 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	assign_field_value(char *line, int k, t_fields *fields, const char **f)
{
	if (!ft_strncmp(line + k, f[0], 2))
		fill_texture(&fields->no_filename, line + k + 2);
	else if (!ft_strncmp(line + k, f[1], 2))
		fill_texture(&fields->so_filename, line + k + 2);
	else if (!ft_strncmp(line + k, f[2], 2))
		fill_texture(&fields->we_filename, line + k + 2);
	else if (!ft_strncmp(line + k, f[3], 2))
		fill_texture(&fields->ea_filename, line + k + 2);
	else if (!ft_strncmp(line + k, f[4], 1))
		fill_color(fields->floor, line + k + 1);
	else if (!ft_strncmp(line + k, f[5], 1))
		fill_color(fields->core, line + k + 1);
}

int	fill_fields_from_lines(char **tab, t_fields *fields)
{
	const char	*f[6] = {"NO", "SO", "WE", "EA", "F", "C"};
	int			i;
	int			k;

	i = 0;
	while (tab[i])
	{
		k = 0;
		while (tab[i][k] && (tab[i][k] <= 32))
			k++;
		if (is_map_line(tab[i]))
			break ;
		if (ft_strlen(tab[i] + k) > 0)
			assign_field_value(tab[i], k, fields, f);
		i++;
	}
	return (i);
}

char	*find_map_start_ptr(char *file_content)
{
	char	*map_start_ptr;

	map_start_ptr = file_content;
	while (*map_start_ptr)
	{
		while (*map_start_ptr == ' ' || *map_start_ptr == '\t')
			map_start_ptr++;
		if (*map_start_ptr == '1' || *map_start_ptr == '0')
			break ;
		while (*map_start_ptr && *map_start_ptr != '\n')
			map_start_ptr++;
		if (*map_start_ptr == '\n')
			map_start_ptr++;
	}
	if (*map_start_ptr == '\0')
		return (NULL);
	return (map_start_ptr);
}

int	line_has_map_chars(char *line_start, char *line_end)
{
	char	*check_ptr;

	check_ptr = line_start;
	while (check_ptr < line_end)
	{
		if (*check_ptr == '1' || *check_ptr == '0' || *check_ptr == 'N'
			|| *check_ptr == 'S' || *check_ptr == 'E' || *check_ptr == 'W')
			return (1);
		check_ptr++;
	}
	return (0);
}

char	*find_last_valid_line(char *map_start_ptr)
{
	char	*temp_ptr;
	char	*temp_line_start;
	char	*last_valid_line;

	last_valid_line = NULL;
	temp_ptr = map_start_ptr;
	temp_line_start = temp_ptr;
	while (*temp_ptr)
	{
		if (*temp_ptr == '\n')
		{
			if (line_has_map_chars(temp_line_start, temp_ptr))
				last_valid_line = temp_ptr;
			temp_ptr++;
			temp_line_start = temp_ptr;
		}
		else
			temp_ptr++;
	}
	return (last_valid_line);
}

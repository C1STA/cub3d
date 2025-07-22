/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 04:30:00 by dpinto            #+#    #+#             */
/*   Updated: 2025/07/18 06:01:18 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static char	**split_content(char *str)
{
	char	**tab;

	tab = ft_split(str, '\n');
	if (!tab)
	{
		ft_putstr_fd("Error\nFailed to split file\n", 2);
		return (NULL);
	}
	return (tab);
}

static int	validate_required_fields(t_fields *fields, char **tab)
{
	if (!fields->no_filename || !fields->so_filename || !fields->we_filename
		|| !fields->ea_filename || fields->floor[0] == -1
		|| fields->core[0] == -1)
	{
		ft_putstr_fd("Error\nMissing required field(s)\n", 2);
		free_strs(tab);
		return (1);
	}
	return (0);
}

static int	validate_final_map(t_fields *fields, char **tab)
{
	if (find_player_in_map(fields->map))
	{
		free_strs(tab);
		return (1);
	}
	if (check_player_position(fields->map))
	{
		free_strs(tab);
		return (1);
	}
	if (parse_validate_map(fields->map))
	{
		free_strs(tab);
		return (1);
	}
	return (0);
}

int	parse(char *filename, t_fields *fields)
{
	char	*str;
	char	**tab;
	int		map_start;

	str = input_to_str(filename);
	if (!str)
		return (1);
	tab = split_content(str);
	if (!tab)
		return (free(str), 1);
	map_start = parse_fields(tab, fields);
	if (map_start == -1)
		return (free(str), free_strs(tab), 1);
	if (validate_required_fields(fields, tab))
		return (free(str), 1);
	if (check_empty_lines_in_map(str))
		return (free(str), free_strs(tab), 1);
	free(str);
	if (fill_map_from_lines(tab, map_start, fields))
		return (free_strs(tab), ft_putstr_fd("Error\n\
Failed to parse map\n", 2), 1);
	if (validate_final_map(fields, tab))
		return (1);
	free_strs(tab);
	return (0);
}

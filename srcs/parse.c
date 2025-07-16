/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 04:30:00 by dpinto            #+#    #+#             */
/*   Updated: 2025/07/16 01:08:04 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static char	**prepare_file_content(char *filename)
{
	char	*str;
	char	**tab;

	str = input_to_str(filename);
	if (!str)
	{
		ft_putstr_fd("Error\nFailed to read file\n", 2);
		return (NULL);
	}
	if (check_empty_lines_in_map(str))
	{
		free(str);
		return (NULL);
	}
	tab = ft_split(str, '\n');
	free(str);
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
		|| !fields->ea_filename || fields->floor[0] == -1 || fields->core[0] ==
		-1)
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
		return (1);
	if (check_player_position(fields->map))
		return (1);
	if (parse_validate_map(fields->map))
	{
		free_strs(tab);
		return (1);
	}
	return (0);
}

int	parse(char *filename, t_fields *fields)
{
	char	**tab;
	int		map_start;

	tab = prepare_file_content(filename);
	if (!tab)
		return (1);
	map_start = parse_fields(tab, fields);
	if (map_start == -1)
	{
		free_strs(tab);
		return (1);
	}
	if (validate_required_fields(fields, tab))
		return (1);
	if (fill_map_from_lines(tab, map_start, fields))
	{
		free_strs(tab);
		ft_putstr_fd("Error\nFailed to parse map\n", 2);
		return (1);
	}
	if (validate_final_map(fields, tab))
		return (1);
	free_strs(tab);
	return (0);
}

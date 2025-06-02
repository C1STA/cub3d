/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:42:45 by dpinto            #+#    #+#             */
/*   Updated: 2025/06/02 02:38:14 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static int	check_and_read_file(char *filename, char **str)
{
	if (check_ext(filename))
	{
		ft_putstr_fd("Error\nWrong extension!\n", 2);
		return (1);
	}
	*str = input_to_str(filename);
	if (!*str)
		return (1);
	return (0);
}

static int	process_map(char **tab, t_fields *fields)
{
	int	map_start;

	map_start = find_map_start(tab);
	if (map_start == -1)
		return (1);
	if (map_start == -1 || parse_map(tab, map_start, fields))
		return (1);
	return (0);
}

int	parse(char *filename, t_fields *fields)
{
	char	*str;
	char	**tab;

	if (check_and_read_file(filename, &str))
		return (1);
	tab = ft_split(str, '\n');
	free(str);
	if (!tab)
		return (1);
	if (parse_fields(tab, fields))
	{
		free_strs(tab);
		return (1);
	}
	if (process_map(tab, fields))
	{
		free_strs(tab);
		return (1);
	}
	free_strs(tab);
	return (0);
}

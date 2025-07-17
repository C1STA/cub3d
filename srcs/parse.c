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

#include "cube3d.h"

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
		return (ft_putstr_fd("Error\nMap \
starting point not recognized\n", 2), 1);
	if (parse_map(tab, map_start, fields))
		return (1);
	return (0);
}

int	empty_lines_map(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] <= 32)
			i++;
		if (str[i] == '1' || str[i] == '0')
			break ;
		while (str[i] && str[i] != '\n')
			i++;
		if (str[i] == '\n')
			i++;
	}
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] == '\n' && str[i - 1] == '\n')
			return (ft_putstr_fd("Error\nEmpty lines \
within or at the end of the map\n", 2), 1);
		i++;
	}
	return (0);
}

int	parse(char *filename, t_fields *fields)
{
	char	*str;
	char	**tab;

	if (check_and_read_file(filename, &str))
		return (1);
	tab = ft_split(str, '\n');
	if (!tab)
		return (free(str), 1);
	if (parse_fields(tab, fields))
		return (free(str), free_strs(tab), 1);
	if (empty_lines_map(str))
		return (free(str), free_strs(tab), 1);
	if (process_map(tab, fields))
		return (free(str), free_strs(tab), 1);
	return (free(str), free_strs(tab), 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:42:45 by dpinto            #+#    #+#             */
/*   Updated: 2025/07/04 04:05:02 by dpinto           ###   ########.fr       */
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

static int	is_valid_identifier(const char *line)
{
	const char	*ids[] = {"NO", "SO", "WE", "EA", "F", "C"};
	int			i;
	int			j;

	i = 0;
	while (line && line[i] == ' ')
		i++;
	if (!line[i])
		return (1);
	j = 0;
	while (j < 6)
	{
		if (!ft_strncmp(line + i, ids[j], ft_strlen(ids[j])))
			return (1);
		j++;
	}
	return (0);
}

static int	check_identifiers(char **tab, int map_start)
{
	int	i;

	i = 0;
	while (tab[i] && (map_start == -1 || i < map_start))
	{
		if (ft_strlen(tab[i]) > 0 && !is_valid_identifier(tab[i]))
		{
			ft_putstr_fd("Error\nInvalid identifier: ", 2);
			ft_putstr_fd(tab[i], 2);
			ft_putstr_fd("\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	parse(char *filename, t_fields *fields)
{
	char	*str;
	char	**tab;
	int		map_start;

	if (check_and_read_file(filename, &str))
		return (1);
	tab = ft_split(str, '\n');
	free(str);
	if (!tab)
		return (1);
	map_start = find_map_start(tab);
	if (check_identifiers(tab, map_start))
	{
		free_strs(tab);
		return (1);
	}
	if (parse_fields(tab, fields) || process_map(tab, fields))
	{
		free_strs(tab);
		return (1);
	}
	free_strs(tab);
	return (0);
}

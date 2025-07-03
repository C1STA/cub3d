/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fields_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:42:45 by dpinto            #+#    #+#             */
/*   Updated: 2025/06/02 03:19:02 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	process_field_line(char *line, const char *field, t_fields *fields)
{
	char	**raws;
	int		result;

	raws = ft_split(line, ' ');
	if (!raws)
		return (0);
	if (get_tab_len(raws) > 2)
	{
		free_strs(raws);
		return (0);
	}
	result = 0;
	if (!ft_strncmp(raws[0], field, ft_strlen(field) + 1))
	{
		fill_fields(fields, raws, field);
		result = 1;
	}
	free_strs(raws);
	return (result);
}

int	fields_is_present(char **tab, const char *field, t_fields *fields)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tab[i] && count < 6)
	{
		if (ft_strlen(tab[i]) > 0)
		{
			if (process_field_line(tab[i], field, fields))
				return (1);
			count++;
		}
		i++;
	}
	return (0);
}

int	check_required_field(char **tab, t_fields *fields)
{
	int			i;
	const char	*f[6] = {"NO", "SO", "WE", "EA", "F", "C"};

	i = 0;
	while (i < 6)
	{
		if (!fields_is_present(tab, f[i], fields))
			return (1);
		i++;
	}
	return (0);
}

static int	check_map_line(char *line, int fields_found)
{
	int	j;

	j = 0;
	while (line[j] && line[j] == ' ')
		j++;
	if (line[j] == '1' || line[j] == '0')
	{
		if (fields_found == 6)
			return (1);
		return (-1);
	}
	else if (line[j] != '\0')
		return (2);
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

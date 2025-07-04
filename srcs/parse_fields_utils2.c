/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fields_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:42:45 by dpinto            #+#    #+#             */
/*   Updated: 2025/07/04 04:11:38 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static int	check_field_line_present(char **tab, const char *field,
		t_fields *fields, int *count)
{
	int	res;
	int	i;

	i = 0;
	while (tab[i] && *count < 6)
	{
		if (ft_strlen(tab[i]) > 0)
		{
			res = process_field_line(tab[i], field, fields);
			if (res == -1)
				return (-1);
			if (res == 1)
				return (1);
			(*count)++;
		}
		i++;
	}
	return (0);
}

int	fields_is_present(char **tab, const char *field, t_fields *fields)
{
	int	i;
	int	count;
	int	res;

	i = 0;
	count = 0;
	while (tab[i] && count < 6)
	{
		if (ft_strlen(tab[i]) > 0)
		{
			res = process_field_line(tab[i], field, fields);
			if (res == -1)
				return (-1);
			if (res == 1)
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
	int			res;

	i = 0;
	while (i < 6)
	{
		res = fields_is_present(tab, f[i], fields);
		if (res == -1)
			return (1);
		if (!res)
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

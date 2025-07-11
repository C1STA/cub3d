/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 00:55:00 by dpinto            #+#    #+#             */
/*   Updated: 2025/07/12 01:13:28 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	is_map_line(const char *line)
{
	int	k;

	k = 0;
	while (line[k] && (line[k] == ' ' || line[k] == '\t'))
		k++;
	if (line[k] == '1' || line[k] == '0')
		return (1);
	return (0);
}

int	check_field_identifier(char *line, int k, int *found, const char **f)
{
	int	j;

	j = 0;
	while (f[j])
	{
		if (!ft_strncmp(line + k, f[j], ft_strlen(f[j])))
		{
			if (found[j])
				return (1);
			found[j] = 1;
			return (0);
		}
		j++;
	}
	return (1);
}

int	validate_field_line(char *line, int *found, const char **f)
{
	int	k;

	k = 0;
	while (line[k] && (line[k] <= 32))
		k++;
	if (ft_strlen(line + k) > 0)
		return (check_field_identifier(line, k, found, f));
	return (0);
}

int	parse_fields(char **tab)
{
	int			found[6];
	const char	*f[6] = {"NO", "SO", "WE", "EA", "F", "C"};
	int			i;

	found[0] = 0;
	found[1] = 0;
	found[2] = 0;
	found[3] = 0;
	found[4] = 0;
	found[5] = 0;
	i = 0;
	while (tab[i])
	{
		if (is_map_line(tab[i]))
			break ;
		if (validate_field_line(tab[i], found, f))
			return (1);
		i++;
	}
	return (0);
}

int	is_empty_line(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

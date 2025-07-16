/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 03:52:00 by dpinto            #+#    #+#             */
/*   Updated: 2025/07/16 04:03:48 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

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
			{
				ft_putstr_fd("Error\nDuplicate field\n", 2);
				return (1);
			}
			found[j] = 1;
			return (0);
		}
		j++;
	}
	ft_putstr_fd("Error\nInvalid identifier: ", 2);
	ft_putstr_fd(line + k, 2);
	ft_putstr_fd("\n", 2);
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

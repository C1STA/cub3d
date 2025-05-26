/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fields_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:42:45 by dpinto            #+#    #+#             */
/*   Updated: 2025/05/26 01:47:42 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	fields_is_present(char **tab, const char *field, t_fields *fields)
{
	int		i;
	int		count;
	char	**raws;

	i = 0;
	count = 0;
	while (tab[i] && count < 6)
	{
		if (ft_strlen(tab[i]) > 0)
		{
			raws = ft_split(tab[i], ' ');
			if (!raws)
				return (0);
			if (!ft_strncmp(raws[0], field, ft_strlen(field) + 1))
			{
				fill_fields(fields, raws, field);
				free_strs(raws);
				return (1);
			}
			free_strs(raws);
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

int	find_map_start(char **tab)
{
	int i;
	int j;
	int fields_found;

	i = 0;
	fields_found = 0;
	while (tab[i])
	{
		if (ft_strlen(tab[i]) > 0)
		{
			j = 0;
			while (tab[i][j] && tab[i][j] == ' ')
				j++;
			if (tab[i][j] == '1' || tab[i][j] == '0')
			{
				if (fields_found >= 6)
					return (i);
			}
			else if (tab[i][j] != '\0')
				fields_found++;
		}
		i++;
	}
	return (-1);
}
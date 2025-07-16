/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 00:55:00 by dpinto            #+#    #+#             */
/*   Updated: 2025/07/16 01:06:29 by dpinto           ###   ########.fr       */
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
			{
				ft_putstr_fd("Error\nDuplicate field\n", 2);
				return (1);
			}
			found[j] = 1;
			return (0);
		}
		j++;
	}
	// Champ invalide trouvé
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

int	parse_fields(char **tab, t_fields *fields)
{
	int			found[6];
	const char	*f[6] = {"NO", "SO", "WE", "EA", "F", "C"};
	int			i;
	int			k;
	int			j;
	int			valid;

	found[0] = 0;
	found[1] = 0;
	found[2] = 0;
	found[3] = 0;
	found[4] = 0;
	found[5] = 0;
	i = 0;
	while (tab[i])
	{
		k = 0;
		while (tab[i][k] && (tab[i][k] <= 32))
			k++;
		if (is_map_line(tab[i]))
			return (i);
		if (ft_strlen(tab[i] + k) > 0)
		{
			j = 0;
			valid = 0;
			for (j = 0; j < 6; j++)
			{
				if (!ft_strncmp(tab[i] + k, f[j], ft_strlen(f[j])))
				{
					if (found[j])
					{
						ft_putstr_fd("Error\nDuplicate field\n", 2);
						return (-1);
					}
					found[j] = 1;
					if (j == 0)
						fill_texture(&fields->no_filename, tab[i] + k + 2);
					else if (j == 1)
						fill_texture(&fields->so_filename, tab[i] + k + 2);
					else if (j == 2)
						fill_texture(&fields->we_filename, tab[i] + k + 2);
					else if (j == 3)
						fill_texture(&fields->ea_filename, tab[i] + k + 2);
					else if (j == 4)
						fill_color(fields->floor, tab[i] + k + 1);
					else if (j == 5)
						fill_color(fields->core, tab[i] + k + 1);
					valid = 1;
					break ;
				}
			}
			if (!valid)
			{
				ft_putstr_fd("Error\nInvalid identifier: ", 2);
				ft_putstr_fd(tab[i] + k, 2);
				ft_putstr_fd("\n", 2);
				return (-1);
			}
		}
		i++;
	}
	return (-1);
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

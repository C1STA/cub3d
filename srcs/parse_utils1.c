/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 00:55:00 by dpinto            #+#    #+#             */
/*   Updated: 2025/07/18 05:55:05 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void	init_found_array(int *found)
{
	found[0] = 0;
	found[1] = 0;
	found[2] = 0;
	found[3] = 0;
	found[4] = 0;
	found[5] = 0;
}

static int	fill_field_by_index(int j, char *value, t_fields *fields)
{
	if (j == 0)
		fill_texture(&fields->no_filename, value);
	else if (j == 1)
		fill_texture(&fields->so_filename, value);
	else if (j == 2)
		fill_texture(&fields->we_filename, value);
	else if (j == 3)
		fill_texture(&fields->ea_filename, value);
	else if (j == 4)
	{
		if (fill_color(fields->floor, value))
			return (1);
	}
	else if (j == 5)
	{
		if (fill_color(fields->core, value))
			return (1);
	}
	return (0);
}

static int	process_valid_field(int j, int *found, char *value,
		t_fields *fields)
{
	if (found[j])
	{
		ft_putstr_fd("Error\nDuplicate field\n", 2);
		return (-1);
	}
	found[j] = 1;
	if (fill_field_by_index(j, value, fields))
		return (-1);
	return (0);
}

static int	process_field_line(char *line, int k, int *found, t_fields *fields)
{
	const char	*f[6] = {"NO", "SO", "WE", "EA", "F", "C"};
	int			j;
	char		tmp[4];

	j = 0;
	while ((line + k)[j] && (line + k)[j] > 32 && j < 3)
	{
		tmp[j] = (line + k)[j];
		j++;
	}
	tmp[j] = '\0';
	j = 0;
	while (j < 6)
	{
		if (!ft_strncmp(tmp, f[j], ft_strlen(f[j]) + 1))
		{
			if (j < 4)
				return (process_valid_field(j, found, line + k + 2, fields));
			else
				return (process_valid_field(j, found, line + k + 1, fields));
		}
		j++;
	}
	return (ft_putstr_fd("Error\nInvalid identifier: ", 2), \
ft_putstr_fd(line + k, 2), ft_putstr_fd("\n", 2), -1);
}

int	parse_fields(char **tab, t_fields *fields)
{
	int	found[6];
	int	i;
	int	k;

	init_found_array(found);
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
			if (process_field_line(tab[i], k, found, fields) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}

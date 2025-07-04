/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fields.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:42:45 by dpinto            #+#    #+#             */
/*   Updated: 2025/06/02 02:01:25 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	fill_color(int *color, char *str)
{
	char	**rgb;
	int		i;

	rgb = ft_split(str, ',');
	if (!rgb)
		return ;
	i = 0;
	while (rgb[i] && i < 3)
	{
		color[i] = ft_atoi(rgb[i]);
		i++;
	}
	free_strs(rgb);
}

void	fill_texture(char **dest, char *src)
{
	*dest = ft_strdup(src);
}

void	fill_fields(t_fields *fields, char **raws, const char *field)
{
	if (!ft_strncmp(field, "NO", 3))
		fill_texture(&fields->no_filename, raws[1]);
	else if (!ft_strncmp(field, "SO", 3))
		fill_texture(&fields->so_filename, raws[1]);
	else if (!ft_strncmp(field, "WE", 3))
		fill_texture(&fields->we_filename, raws[1]);
	else if (!ft_strncmp(field, "EA", 3))
		fill_texture(&fields->ea_filename, raws[1]);
	else if (!ft_strncmp(field, "F", 2))
		fill_color(fields->floor, raws[1]);
	else if (!ft_strncmp(field, "C", 2))
		fill_color(fields->core, raws[1]);
}

int	parse_fields(char **tab, t_fields *fields)
{
	if (check_required_field(tab, fields))
	{
		ft_putstr_fd("Error\nInvalid field information\n", 2);
		return (1);
	}
	if (validate_textures(fields))
	{
		ft_putstr_fd("Error\nInvalid texture file\n", 2);
		return (1);
	}
	if (validate_colors(fields))
	{
		ft_putstr_fd("Error\nInvalid color value\n", 2);
		return (1);
	}
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

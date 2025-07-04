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

int	check_commas_and_digits(char *str)
{
	int	i;
	int	count;

	if (!str)
		return (1);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		else if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	if (count != 2)
		return (1);
	return (0);
}

int	fill_color(int *color, char *str)
{
	char	**rgb;
	int		i;

	if (check_commas_and_digits(str))
		return (1);
	rgb = ft_split(str, ',');
	if (!rgb)
		return (1);
	i = 0;
	while (rgb[i] && i < 3)
	{
		color[i] = ft_atoi(rgb[i]);
		i++;
	}
	free_strs(rgb);
	return (0);
}

int	fill_texture(char **dest, char *src)
{
	*dest = ft_strdup(src);
	if (!*dest)
		return (1);
	return (0);
}

int	fill_fields(t_fields *fields, char **raws, const char *field)
{
	if (!ft_strncmp(field, "NO", 3) && \
!fill_texture(&fields->no_filename, raws[1]))
		return (0);
	else if (!ft_strncmp(field, "SO", 3) && \
!fill_texture(&fields->so_filename, raws[1]))
		return (0);
	else if (!ft_strncmp(field, "WE", 3) && \
!fill_texture(&fields->we_filename, raws[1]))
		return (0);
	else if (!ft_strncmp(field, "EA", 3) && \
!fill_texture(&fields->ea_filename, raws[1]))
		return (0);
	else if (!ft_strncmp(field, "F", 2) && !fill_color(fields->floor, raws[1]))
		return (0);
	else if (!ft_strncmp(field, "C", 2) && !fill_color(fields->core, raws[1]))
		return (0);
	return (1);
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

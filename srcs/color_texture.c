/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 03:05:00 by dpinto            #+#    #+#             */
/*   Updated: 2025/07/18 05:54:57 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	process_color_values(int *color, char **rgb)
{
	int	i;
	int	val;

	i = 0;
	while (i < 3)
	{
		val = ft_atoi(rgb[i]);
		if (val < 0 || val > 255)
		{
			ft_putstr_fd("Error\nColor value must be between 0 and 255\n", 2);
			free_strs(rgb);
			return (1);
		}
		color[i] = val;
		i++;
	}
	return (0);
}

int	fill_color(int *color, char *str)
{
	char	**rgb;

	while (*str == ' ' || *str == '\t')
		str++;
	if (validate_color_format(str))
		return (1);
	rgb = ft_split(str, ',');
	if (!rgb)
	{
		ft_putstr_fd("Error\nInvalid color format\n", 2);
		return (1);
	}
	if (process_color_values(color, rgb))
		return (1);
	free_strs(rgb);
	return (0);
}

void	fill_texture(char **dest, char *src)
{
	if (*dest)
		free(*dest);
	while (*src == ' ' || *src == '\t')
		src++;
	*dest = ft_strdup(src);
}

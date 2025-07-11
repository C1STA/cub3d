/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 03:05:00 by dpinto            #+#    #+#             */
/*   Updated: 2025/07/12 01:09:50 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	process_color_values(int *color, char **rgb)
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
			exit(1);
		}
		color[i] = val;
		i++;
	}
}

void	fill_color(int *color, char *str)
{
	char	**rgb;

	while (*str == ' ' || *str == '\t')
		str++;
	validate_color_format(str);
	rgb = ft_split(str, ',');
	if (!rgb)
	{
		ft_putstr_fd("Error\nInvalid color format\n", 2);
		exit(1);
	}
	process_color_values(color, rgb);
	free_strs(rgb);
}

void	fill_texture(char **dest, char *src)
{
	if (*dest)
		free(*dest);
	while (*src == ' ' || *src == '\t')
		src++;
	*dest = ft_strdup(src);
}

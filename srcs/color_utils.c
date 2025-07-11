/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 01:10:00 by dpinto            #+#    #+#             */
/*   Updated: 2025/07/12 01:10:02 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	check_comma_validity(char *str, int i, int comma_count)
{
	if (i == 0 || str[i - 1] == ',' || str[i + 1] == ',' || str[i + 1] == '\0')
	{
		ft_putstr_fd("Error\nInvalid color format: comma\n", 2);
		exit(1);
	}
	return (comma_count + 1);
}

void	validate_character(char c, int i, char *str, int *comma_count)
{
	if (c == ',')
		*comma_count = check_comma_validity(str, i, *comma_count);
	else if (c < '0' || c > '9')
	{
		ft_putstr_fd("Error\nColor components must be numeric\n", 2);
		exit(1);
	}
}

int	validate_color_format(char *str)
{
	int	i;
	int	comma_count;

	comma_count = 0;
	i = 0;
	while (str[i])
	{
		validate_character(str[i], i, str, &comma_count);
		i++;
	}
	if (comma_count != 2)
	{
		ft_putstr_fd("Error\nColor must have exactly 3 values (R,G,B)\n", 2);
		exit(1);
	}
	return (0);
}

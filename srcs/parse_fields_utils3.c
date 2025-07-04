/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fields_utils3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 04:10:00 by dpinto            #+#    #+#             */
/*   Updated: 2025/07/04 04:13:14 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static int	handle_invalid_identifier(char **raws)
{
	ft_putstr_fd("Error\nInvalid identifier: ", 2);
	ft_putstr_fd(raws[0], 2);
	ft_putstr_fd("\n", 2);
	free_strs(raws);
	return (-1);
}

static int	test_and_free_raws(char **raws)
{
	if (get_tab_len(raws) > 2)
	{
		free_strs(raws);
		return (1);
	}
	return (0);
}

int	process_field_line(char *line, const char *field, t_fields *fields)
{
	char	**raws;
	int		result;

	raws = ft_split(line, ' ');
	if (!raws)
		return (0);
	if (test_and_free_raws(raws))
		return (0);
	result = 0;
	if (!ft_strncmp(raws[0], field, ft_strlen(field) + 1))
	{
		if (fill_fields(fields, raws, field))
			return (handle_invalid_identifier(raws));
		result = 1;
	}
	free_strs(raws);
	return (result);
}

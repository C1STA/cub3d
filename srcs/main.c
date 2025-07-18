/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:42:45 by dpinto            #+#    #+#             */
/*   Updated: 2025/07/18 06:37:00 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static int	init_and_parse(char *filename, t_fields *fields)
{
	int	ret;

	init_fields(fields);
	ret = parse(filename, fields);
	if (ret)
	{
		free_fields(fields);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_fields	fields;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nUsage: ./cub3D <map.cub>\n", 2);
		return (1);
	}
	if (check_ext(argv[1]))
	{
		ft_putstr_fd("Error\nInvalid file extension. Use .cub files only\n", 2);
		return (1);
	}
	if (init_and_parse(argv[1], &fields))
		return (1);
	if (init_window(&fields))
	{
		free_fields(&fields);
		return (1);
	}
	free_fields(&fields);
	return (0);
}

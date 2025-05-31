/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:42:45 by dpinto            #+#    #+#             */
/*   Updated: 2025/05/31 05:42:56 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	main(int argc, char **argv)
{
	t_fields	fields;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nUsage: ./cub3D <map.cub>\n", 2);
		return (1);
	}
	init_fields(&fields);
	if (parse(argv[1], &fields))
	{
		ft_putstr_fd("Error\nInvalid map!\n", 2);
		free_fields(&fields);
		return (1);
	}
	// print_fields(&fields);
	if (init_window(&fields))
	{
		free_fields(&fields);
		return (1);
	}
	free_fields(&fields);
	return (0);
}

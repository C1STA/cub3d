/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:23:04 by dpinto            #+#    #+#             */
/*   Updated: 2025/05/18 06:20:56 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	main(int ac, char **av)
{
	t_fields	fields;

	if (ac != 2)
	{
		ft_putstr_fd("One arguments needed\n", 2);
		exit(EXIT_FAILURE);
	}
	if (parse(av[1], &fields))
		exit(EXIT_FAILURE);
	print_fields(&fields);
	free(fields.no_filename);
	free(fields.so_filename);
	free(fields.we_filename);
	free(fields.ea_filename);
	return (0);
}

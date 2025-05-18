/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_fields.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 06:12:41 by dpinto            #+#    #+#             */
/*   Updated: 2025/05/18 06:18:23 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	print_fields(t_fields *fields)
{
	printf("%s\n", fields->no_filename);
	printf("%s\n", fields->so_filename);
	printf("%s\n", fields->we_filename);
	printf("%s\n", fields->ea_filename);
	printf("F: %d %d %d\n", fields->floor[0], fields->floor[1],
		fields->floor[2]);
	printf("C: %d %d %d\n", fields->core[0], fields->core[1], fields->core[2]);
}
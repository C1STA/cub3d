/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:42:45 by dpinto            #+#    #+#             */
/*   Updated: 2025/06/02 03:24:25 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

size_t	get_tab_len(char **tab)
{
	size_t	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}

void	init_fields(t_fields *fields)
{
	fields->no_filename = NULL;
	fields->so_filename = NULL;
	fields->we_filename = NULL;
	fields->ea_filename = NULL;
	fields->floor[0] = -1;
	fields->floor[1] = -1;
	fields->floor[2] = -1;
	fields->core[0] = -1;
	fields->core[1] = -1;
	fields->core[2] = -1;
	fields->map = NULL;
	fields->mlx = NULL;
	fields->win = NULL;
	fields->no_texture = NULL;
	fields->so_texture = NULL;
	fields->we_texture = NULL;
	fields->ea_texture = NULL;
	fields->ray = NULL;
}

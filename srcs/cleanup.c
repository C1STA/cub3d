/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:42:45 by dpinto            #+#    #+#             */
/*   Updated: 2025/05/26 02:54:20 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	cleanup_mlx(t_fields *fields)
{
	if (fields->texture)
		mlx_destroy_image(fields->mlx, fields->texture);
	if (fields->win)
		mlx_destroy_window(fields->mlx, fields->win);
	if (fields->mlx)
	{
		mlx_destroy_display(fields->mlx);
		free(fields->mlx);
	}
}
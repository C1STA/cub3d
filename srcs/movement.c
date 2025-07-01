/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 02:04:45 by dpinto            #+#    #+#             */
/*   Updated: 2025/05/28 02:15:04 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	handle_movement(int keycode, t_fields *fields)
{
	int	moved;

	moved = 0;
	if (keycode == XK_Escape)
	{
		free_fields(fields);
		exit(0);
	}
	moved = handle_wasd(keycode, fields);
	if (!moved)
		moved = handle_rotation(keycode, fields);
	if (moved)
	{
		cast_rays(fields, fields->ray);
		return (1);
	}
	return (0);
}

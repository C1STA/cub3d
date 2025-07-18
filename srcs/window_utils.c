/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 06:30:00 by dpinto            #+#    #+#             */
/*   Updated: 2025/07/18 06:33:01 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	get_screen_size(void *mlx, int *width, int *height)
{
	int	screen_width;
	int	screen_height;

	mlx_get_screen_size(mlx, &screen_width, &screen_height);
	*width = screen_width;
	*height = screen_height;
	return (0);
}

int	limit_window_size(void *mlx, int *width, int *height)
{
	int	screen_width;
	int	screen_height;

	get_screen_size(mlx, &screen_width, &screen_height);
	if (*width <= 0)
		*width = 800;
	if (*height <= 0)
		*height = 600;
	if (*width > screen_width)
		*width = screen_width;
	if (*height > screen_height)
		*height = screen_height;
	return (0);
}

int	handle_close(t_fields *fields)
{
	mlx_loop_end(fields->mlx);
	return (0);
}

int	handle_keypress(int keycode, t_fields *fields)
{
	if (keycode == XK_Escape)
		mlx_loop_end(fields->mlx);
	else
		handle_movement(keycode, fields);
	return (0);
}

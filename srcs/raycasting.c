/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 05:14:18 by dpinto            #+#    #+#             */
/*   Updated: 2025/07/11 00:02:34 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"
#include <math.h>

static void	cast_single_ray(t_fields *fields, t_ray *ray, t_img *img, int x)
{
	init_ray_dir(ray, fields, x);
	init_dda_steps(ray);
	perform_dda(ray, fields);
	calculate_wall_height(ray);
	draw_textured_line(img, x, ray, fields);
}

void	cast_rays(t_fields *fields, t_ray *ray)
{
	int		x;
	t_img	img;

	img.img = mlx_new_image(fields->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		cast_single_ray(fields, ray, &img, x);
		x++;
	}
	mlx_put_image_to_window(fields->mlx, fields->win, img.img, 0, 0);
	mlx_destroy_image(fields->mlx, img.img);
}

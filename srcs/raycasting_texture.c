/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 05:14:18 by dpinto            #+#    #+#             */
/*   Updated: 2025/05/28 05:37:07 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"
#include <math.h>

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	get_texture_color(void *texture, int tex_x, int tex_y)
{
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	addr = mlx_get_data_addr(texture, &bits_per_pixel, &line_length, &endian);
	return (*(unsigned int *)(addr + (tex_y * line_length + tex_x
			* (bits_per_pixel / 8))));
}

double	get_wall_x(t_ray *ray)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = ray->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = ray->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

void	*select_texture(t_ray *ray, t_fields *fields)
{
	if (ray->side == 0 && ray->ray_dir_x > 0)
		return (fields->ea_texture);
	else if (ray->side == 0)
		return (fields->we_texture);
	else if (ray->ray_dir_y > 0)
		return (fields->so_texture);
	return (fields->no_texture);
}

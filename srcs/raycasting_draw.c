/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 05:14:18 by dpinto            #+#    #+#             */
/*   Updated: 2025/05/29 05:49:40 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	draw_ceiling(t_img *img, int x, int draw_start, int *color)
{
	int	y;

	y = 0;
	while (y < draw_start)
		my_mlx_pixel_put(img, x, y++,
			color[0] << 16 | color[1] << 8 | color[2]);
}

void	draw_floor(t_img *img, int x, int draw_end, int *color)
{
	int	y;

	y = draw_end;
	while (y < WINDOW_HEIGHT)
		my_mlx_pixel_put(img, x, y++,
			color[0] << 16 | color[1] << 8 | color[2]);
}

void	draw_textured_line(t_img *img, int x, t_ray *ray, t_fields *fields)
{
	double	wall_x;
	int		tex_x;
	int		tex_y;
	void	*texture;
	int		y;

	draw_ceiling(img, x, ray->draw_start, fields->core);
	wall_x = get_wall_x(ray);
	texture = select_texture(ray, fields);
	tex_x = (int)(wall_x * fields->tex_width);
	if ((ray->side == 0 && ray->ray_dir_x < 0) || (ray->side == 1
			&& ray->ray_dir_y < 0))
		tex_x = fields->tex_width - tex_x - 1;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)((double)(y - ray->draw_start) * fields->tex_height
				/ (ray->draw_end - ray->draw_start));
		my_mlx_pixel_put(img, x, y++, get_texture_color(texture, tex_x, tex_y));
	}
	draw_floor(img, x, ray->draw_end, fields->floor);
}

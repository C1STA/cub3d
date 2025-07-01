/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 05:14:18 by dpinto            #+#    #+#             */
/*   Updated: 2025/07/01 04:17:31 by dpinto           ###   ########.fr       */
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

// Dessine la colonne de mur à la bonne hauteur,
//	avec la bonne partie de la texture, sur l’image.
void	draw_textured_line(t_img *img, int x, t_ray *ray, t_fields *fields)
{
	t_tex_data	tex;
	int			y;
	int			tex_y;

	draw_ceiling(img, x, ray->draw_start, fields->core);
	tex.wall_x = get_wall_x(ray);
	tex.texture = select_texture(ray, fields);
	tex.tex_x = (int)(tex.wall_x * fields->tex_width);
	if ((ray->side == 0 && ray->ray_dir_x < 0) || (ray->side == 1
			&& ray->ray_dir_y < 0))
		tex.tex_x = fields->tex_width - tex.tex_x - 1;
	tex.step = 1.0 * fields->tex_height / ray->line_height;
	tex.tex_pos = (ray->draw_start - WINDOW_HEIGHT / 2 + ray->line_height / 2)
		* tex.step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)tex.tex_pos & (fields->tex_height - 1);
		tex.tex_pos += tex.step;
		my_mlx_pixel_put(img, x, y++, get_texture_color(tex.texture, tex.tex_x,
				tex_y));
	}
	draw_floor(img, x, ray->draw_end, fields->floor);
}

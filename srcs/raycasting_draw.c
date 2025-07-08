/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 05:14:18 by dpinto            #+#    #+#             */
/*   Updated: 2025/07/09 01:38:47 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	draw_ceiling(t_img *img, int x, int draw_start, int *color)
{
	int	y;
	int	rgb_color;

	rgb_color = (color[0] << 16) | (color[1] << 8) | color[2];
	y = 0;
	while (y < draw_start)
		my_mlx_pixel_put(img, x, y++, rgb_color);
}

void	draw_floor(t_img *img, int x, int draw_end, int *color)
{
	int	y;
	int	rgb_color;

	rgb_color = (color[0] << 16) | (color[1] << 8) | color[2];
	y = draw_end;
	while (y < WINDOW_HEIGHT)
		my_mlx_pixel_put(img, x, y++, rgb_color);
}

// Dessine la colonne de mur à la bonne hauteur,
//	avec la bonne partie de la texture, sur l'image.
void	draw_textured_line(t_img *img, int x, t_ray *ray, t_fields *fields)
{
	t_tex_data	tex;
	int			y;
	int			tex_y;

	draw_ceiling(img, x, ray->draw_start, fields->core);
	tex.wall_x = get_wall_x(ray);
	tex.texture = select_texture(ray, fields);
	if (!tex.texture)
		return ;
	tex.tex_x = (int)(tex.wall_x * fields->tex_width);
	if ((ray->side == 0 && ray->ray_dir_x < 0) || (ray->side == 1
			&& ray->ray_dir_y < 0))
		tex.tex_x = fields->tex_width - tex.tex_x - 1;
	if (tex.tex_x < 0 || tex.tex_x >= fields->tex_width)
		tex.tex_x = 0;
	tex.step = 1.0 * fields->tex_height / ray->line_height;
	tex.tex_pos = (ray->draw_start - WINDOW_HEIGHT / 2 + ray->line_height / 2)
		* tex.step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		if (y >= 0 && y < WINDOW_HEIGHT) // Sécurité bornes image
		{
			tex_y = (int)tex.tex_pos & (fields->tex_height - 1);
			if (tex_y < 0 || tex_y >= fields->tex_height)
				tex_y = 0;
			my_mlx_pixel_put(img, x, y, get_texture_color(tex.texture,
					tex.tex_x, tex_y));
		}
		tex.tex_pos += tex.step;
		y++;
	}
	draw_floor(img, x, ray->draw_end + 1, fields->floor);
}

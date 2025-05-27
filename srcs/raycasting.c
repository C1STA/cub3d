#include "../includes/cube3d.h"
#include <math.h>

static void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static int	get_texture_color(void *texture, int tex_x, int tex_y)
{
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	addr = mlx_get_data_addr(texture, &bits_per_pixel, &line_length, &endian);
	return (*(unsigned int *)(addr + (tex_y * line_length + tex_x
				* (bits_per_pixel / 8))));
}

static void	draw_textured_line(t_img *img, int x, t_ray *ray, t_fields *fields)
{
	int		y;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	void	*texture;

	y = 0;
	while (y < ray->draw_start)
		my_mlx_pixel_put(img, x, y++,
			fields->core[0] << 16 | fields->core[1] << 8 | fields->core[2]);
	if (ray->side == 0)
		wall_x = ray->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = ray->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		texture = fields->ea_texture;
	else if (ray->side == 0)
		texture = fields->we_texture;
	else if (ray->ray_dir_y > 0)
		texture = fields->so_texture;
	else
		texture = fields->no_texture;
	tex_x = (int)(wall_x * fields->tex_width);
	if ((ray->side == 0 && ray->ray_dir_x < 0) || (ray->side == 1
			&& ray->ray_dir_y < 0))
		tex_x = fields->tex_width - tex_x - 1;
	while (y < ray->draw_end)
	{
		tex_y = (int)((double)(y - ray->draw_start) * fields->tex_height
				/ (ray->draw_end - ray->draw_start));
		my_mlx_pixel_put(img, x, y++, get_texture_color(texture, tex_x, tex_y));
	}
	while (y < WINDOW_HEIGHT)
		my_mlx_pixel_put(img, x, y++,
			fields->floor[0] << 16 | fields->floor[1] << 8 | fields->floor[2]);
}

static void	init_ray_dir(t_ray *ray, t_fields *fields, int x)
{
	(void)fields;
	ray->camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
	ray->ray_dir_x = ray->dir_x + ray->plane_x * ray->camera_x;
	ray->ray_dir_y = ray->dir_y + ray->plane_y * ray->camera_x;
	ray->map_x = (int)ray->pos_x;
	ray->map_y = (int)ray->pos_y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

static void	init_dda_steps(t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_dist_y;
	}
}

static void	perform_dda(t_ray *ray, t_fields *fields)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (fields->map->grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

static void	calculate_wall_height(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - ray->pos_x + (1 - ray->step_x) / 2)
			/ ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - ray->pos_y + (1 - ray->step_y) / 2)
			/ ray->ray_dir_y;
	// Calcul de la hauteur de la ligne à dessiner
	ray->line_height = (int)(WINDOW_HEIGHT / ray->perp_wall_dist);
	// Calcul du point le plus bas et le plus haut de la ligne
	ray->draw_start = -ray->line_height / 2 + WINDOW_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WINDOW_HEIGHT / 2;
	if (ray->draw_end >= WINDOW_HEIGHT)
		ray->draw_end = WINDOW_HEIGHT - 1;
}

void	cast_rays(t_fields *fields, t_ray *ray)
{
	int x;
	t_img img;

	img.img = mlx_new_image(fields->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		init_ray_dir(ray, fields, x);
		init_dda_steps(ray);
		perform_dda(ray, fields);
		calculate_wall_height(ray);
		draw_textured_line(&img, x, ray, fields);
		x++;
	}
	mlx_put_image_to_window(fields->mlx, fields->win, img.img, 0, 0);
	mlx_destroy_image(fields->mlx, img.img);
}
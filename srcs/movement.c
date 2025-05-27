#include "../includes/cube3d.h"
#include <math.h>

#define MOVE_SPEED 0.08
#define ROT_SPEED 0.05
#define WALL_MARGIN 0.3

static void	rotate_player(t_ray *ray, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = ray->dir_x;
	ray->dir_x = ray->dir_x * cos(rot_speed) - ray->dir_y * sin(rot_speed);
	ray->dir_y = old_dir_x * sin(rot_speed) + ray->dir_y * cos(rot_speed);
	old_plane_x = ray->plane_x;
	ray->plane_x = ray->plane_x * cos(rot_speed) - ray->plane_y
		* sin(rot_speed);
	ray->plane_y = old_plane_x * sin(rot_speed) + ray->plane_y * cos(rot_speed);
}

static int	check_collision(t_fields *fields, double new_x, double new_y)
{
	if (new_x < 0 || new_y < 0 || new_x >= fields->map->width
		|| new_y >= fields->map->height
		|| fields->map->grid[(int)new_y][(int)new_x] == '1'
		|| fields->map->grid[(int)(new_y + WALL_MARGIN)][(int)new_x] == '1'
		|| fields->map->grid[(int)(new_y - WALL_MARGIN)][(int)new_x] == '1'
		|| fields->map->grid[(int)new_y][(int)(new_x + WALL_MARGIN)] == '1'
		|| fields->map->grid[(int)new_y][(int)(new_x - WALL_MARGIN)] == '1')
		return (1);
	return (0);
}

static void	move_player(t_fields *fields, t_ray *ray, double dir_x,
		double dir_y)
{
	double	new_x;
	double	new_y;
	double	margin;

	margin = WALL_MARGIN;
	new_x = ray->pos_x + dir_x * MOVE_SPEED;
	new_y = ray->pos_y + dir_y * MOVE_SPEED;
	if (!check_collision(fields, new_x + dir_x * margin, ray->pos_y))
	{
		ray->pos_x = new_x;
		fields->map->player_x = (int)ray->pos_x;
	}
	if (!check_collision(fields, ray->pos_x, new_y + dir_y * margin))
	{
		ray->pos_y = new_y;
		fields->map->player_y = (int)ray->pos_y;
	}
}

int	handle_movement(int keycode, t_fields *fields)
{
	int moved;

	moved = 0;
	if (keycode == XK_w)
	{
		move_player(fields, fields->ray, fields->ray->dir_x,
			fields->ray->dir_y);
		moved = 1;
	}
	else if (keycode == XK_s)
	{
		move_player(fields, fields->ray, -fields->ray->dir_x,
			-fields->ray->dir_y);
		moved = 1;
	}
	else if (keycode == XK_a)
	{
		move_player(fields, fields->ray, fields->ray->dir_y,
			-fields->ray->dir_x);
		moved = 1;
	}
	else if (keycode == XK_d)
	{
		move_player(fields, fields->ray, -fields->ray->dir_y,
			fields->ray->dir_x);
		moved = 1;
	}
	else if (keycode == XK_Left)
	{
		rotate_player(fields->ray, -ROT_SPEED);
		moved = 1;
	}
	else if (keycode == XK_Right)
	{
		rotate_player(fields->ray, ROT_SPEED);
		moved = 1;
	}

	if (moved)
	{
		cast_rays(fields, fields->ray);
		return (1);
	}
	return (0);
}
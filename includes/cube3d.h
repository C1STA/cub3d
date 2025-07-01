/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 01:34:38 by dpinto            #+#    #+#             */
/*   Updated: 2025/06/19 01:45:18 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define MAP_CHARS "01NSEW "
# define VALID_PLAYER "NSEW"
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720

/* Movement constants */
# define MOVE_SPEED 0.08
# define ROT_SPEED 0.05
# define WALL_MARGIN 0.3

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	char	player_dir;
}			t_map;

typedef struct s_ray
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}			t_ray;

typedef struct s_fields
{
	char	*no_filename;
	char	*so_filename;
	char	*we_filename;
	char	*ea_filename;
	int		floor[3];
	int		core[3];
	t_map	*map;
	void	*mlx;
	void	*win;
	void	*no_texture;
	void	*so_texture;
	void	*we_texture;
	void	*ea_texture;
	int		tex_width;
	int		tex_height;
	t_ray	*ray;
}			t_fields;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img;

typedef struct s_tex_data
{
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
	void	*texture;
}			t_tex_data;

/* Helper functions */
size_t		get_tab_len(char **tab);
char		**free_strs(char **strs);

/* File utils */
int			check_ext(char *filename);
char		*input_to_str(char *filename);

/* Helper init functions */
void		init_fields(t_fields *fields);
void		free_fields(t_fields *fields);
void		cleanup_mlx(t_fields *fields);

/* Parse fields functions */
int			parse(char *filename, t_fields *fields);
int			parse_fields(char **tab, t_fields *fields);
int			check_required_field(char **tab, t_fields *fields);
int			find_map_start(char **tab);
int			fields_is_present(char **tab, const char *field, t_fields *fields);

/* Parse fields utils */
void		fill_color(int *color, char *str);
void		fill_texture(char **dest, char *src);
void		fill_fields(t_fields *fields, char **raws, const char *field);

/* Map utils */
int			get_map_dimensions(char **tab, int start, t_map *map);
char		*pad_line(char *line, int width);
int			copy_map(char **tab, int start, t_map *map);

/* Validation functions */
int			validate_colors(t_fields *fields);
int			validate_textures(t_fields *fields);
int			validate_map(t_map *map);
int			check_walls(t_map *map, int i, int j);

/* Map check functions */
int			check_map_chars(t_map *map);

/* Map parsing functions */
int			parse_map(char **tab, int start_idx, t_fields *fields);

/* Print functions */
void		print_fields(t_fields *fields);

/* Window functions */
int			init_window(t_fields *fields);

/* Movement functions */
int			handle_movement(int keycode, t_fields *fields);

/* Movement utils functions */
void		rotate_player(t_ray *ray, double rot_speed);
int			check_collision(t_fields *fields, double next_x, double next_y);
void		move_player(t_fields *fields, t_ray *ray, double dir_x,
				double dir_y);
int			handle_wasd(int keycode, t_fields *fields);
int			handle_rotation(int keycode, t_fields *fields);

/* Raycasting functions */
void		cast_rays(t_fields *fields, t_ray *ray);

/* Raycasting texture functions */
void		my_mlx_pixel_put(t_img *img, int x, int y, int color);
int			get_texture_color(void *texture, int tex_x, int tex_y);
double		get_wall_x(t_ray *ray);
void		*select_texture(t_ray *ray, t_fields *fields);

/* Raycasting draw functions */
void		draw_ceiling(t_img *img, int x, int draw_start, int *color);
void		draw_floor(t_img *img, int x, int draw_end, int *color);
void		draw_textured_line(t_img *img, int x, t_ray *ray, t_fields *fields);

/* Window texture functions */
void		cleanup_loaded_textures(t_fields *fields);
int			load_textures(t_fields *fields);

#endif

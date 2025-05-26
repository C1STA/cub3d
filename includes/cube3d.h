/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 01:34:38 by dpinto            #+#    #+#             */
/*   Updated: 2025/05/26 02:54:22 by dpinto           ###   ########.fr       */
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

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	char	player_dir;
}			t_map;

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
	void	*texture;
	int		tex_width;
	int		tex_height;
}			t_fields;

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

/* Map check functions */
int			check_map_chars(t_map *map);

/* Map parsing functions */
int			parse_map(char **tab, int start_idx, t_fields *fields);

/* Print functions */
void		print_fields(t_fields *fields);

/* Window functions */
int			init_window(t_fields *fields);

/* New functions */
int			check_walls(t_map *map, int i, int j);

#endif

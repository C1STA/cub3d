/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 04:30:00 by dpinto            #+#    #+#             */
/*   Updated: 2025/07/11 03:04:31 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	is_map_line(const char *line)
{
	int	j;

	j = 0;
	while (line[j] && (line[j] <= 32))
		j++;
	return (line[j] == '1' || line[j] == '0');
}

static int	check_field_identifier(char *line, int k, int *found,
		const char **f)
{
	int	j;
	int	len;

	j = 0;
	while (j < 6)
	{
		len = ft_strlen(f[j]);
		if (!ft_strncmp(line + k, f[j], len) && (line[k + len] == ' ' || line[k
					+ len] == '\t'))
		{
			if (found[j])
			{
				ft_putstr_fd("Error\nDuplicate identifier\n", 2);
				return (1);
			}
			found[j] = 1;
			return (0);
		}
		j++;
	}
	ft_putstr_fd("Error\nInvalid identifier\n", 2);
	return (1);
}

static int	validate_field_line(char *line, int *found, const char **f)
{
	int	k;

	k = 0;
	while (line[k] && (line[k] <= 32))
		k++;
	if (ft_strlen(line + k) > 0)
		return (check_field_identifier(line, k, found, f));
	return (0);
}

int	parse_fields(char **tab)
{
	int			found[6];
	const char	*f[6] = {"NO", "SO", "WE", "EA", "F", "C"};
	int			i;

	found[0] = 0;
	found[1] = 0;
	found[2] = 0;
	found[3] = 0;
	found[4] = 0;
	found[5] = 0;
	i = 0;
	while (tab[i])
	{
		if (is_map_line(tab[i]))
			break ;
		if (validate_field_line(tab[i], found, f))
			return (1);
		i++;
	}
	return (0);
}

static int	is_empty_line(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

static void	assign_field_value(char *line, int k, t_fields *fields,
		const char **f)
{
	if (!ft_strncmp(line + k, f[0], 2))
		fill_texture(&fields->no_filename, line + k + 2);
	else if (!ft_strncmp(line + k, f[1], 2))
		fill_texture(&fields->so_filename, line + k + 2);
	else if (!ft_strncmp(line + k, f[2], 2))
		fill_texture(&fields->we_filename, line + k + 2);
	else if (!ft_strncmp(line + k, f[3], 2))
		fill_texture(&fields->ea_filename, line + k + 2);
	else if (!ft_strncmp(line + k, f[4], 1))
		fill_color(fields->floor, line + k + 1);
	else if (!ft_strncmp(line + k, f[5], 1))
		fill_color(fields->core, line + k + 1);
}

static int	fill_fields_from_lines(char **tab, t_fields *fields)
{
	const char	*f[6] = {"NO", "SO", "WE", "EA", "F", "C"};
	int			i;
	int			k;

	i = 0;
	while (tab[i])
	{
		k = 0;
		while (tab[i][k] && (tab[i][k] <= 32))
			k++;
		if (is_map_line(tab[i]))
			break ;
		if (ft_strlen(tab[i] + k) > 0)
			assign_field_value(tab[i], k, fields, f);
		i++;
	}
	return (i);
}

static int	process_line_dimension(char *line, int *height, int *max_width,
		int *map_started)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && !is_empty_line(line))
	{
		if (len > *max_width)
			*max_width = len;
		(*height)++;
		*map_started = 1;
	}
	else if (*map_started && (len == 0 || is_empty_line(line)))
	{
		ft_putstr_fd("Error\nEmpty line inside map\n", 2);
		return (1);
	}
	return (0);
}

static int	calculate_map_dimensions(char **tab, int map_start, int *height,
		int *max_width)
{
	int	i;
	int	map_started;

	*height = 0;
	*max_width = 0;
	map_started = 0;
	i = map_start;
	while (tab[i])
	{
		if (process_line_dimension(tab[i], height, max_width, &map_started))
			return (1);
		i++;
	}
	return (0);
}

static int	allocate_map_memory(t_fields *fields, int height)
{
	fields->map = malloc(sizeof(t_map));
	if (!fields->map)
		return (1);
	fields->map->grid = malloc(sizeof(char *) * (height + 1));
	if (!fields->map->grid)
		return (1);
	return (0);
}

static int	fill_map_grid(char **tab, int map_start, t_fields *fields,
		int max_width)
{
	char	*padded;
	int		i;
	int		j;
	int		len;

	i = map_start;
	j = 0;
	while (tab[i])
	{
		len = ft_strlen(tab[i]);
		if (len > 0 && !is_empty_line(tab[i]))
		{
			padded = malloc(max_width + 1);
			if (!padded)
				return (1);
			ft_memset(padded, ' ', max_width);
			ft_memcpy(padded, tab[i], len);
			padded[max_width] = '\0';
			fields->map->grid[j] = padded;
			j++;
		}
		i++;
	}
	fields->map->grid[j] = NULL;
	return (0);
}

static int	fill_map_from_lines(char **tab, int map_start, t_fields *fields)
{
	int	height;
	int	max_width;

	if (calculate_map_dimensions(tab, map_start, &height, &max_width))
		return (1);
	if (height == 0)
		return (1);
	if (allocate_map_memory(fields, height))
		return (1);
	if (fill_map_grid(tab, map_start, fields, max_width))
		return (1);
	fields->map->height = height;
	fields->map->width = max_width;
	return (0);
}

static int	process_player_character(t_map *map, int i, int j, int *found)
{
	if (*found)
	{
		ft_putstr_fd("Error\nMultiple player positions\n", 2);
		return (1);
	}
	map->player_x = j;
	map->player_y = i;
	map->player_dir = map->grid[i][j];
	map->grid[i][j] = '0';
	*found = 1;
	return (0);
}

static int	find_player_in_map(t_map *map)
{
	int	i;
	int	j;
	int	found;

	found = 0;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (map->grid[i][j] == 'N' || map->grid[i][j] == 'S'
				|| map->grid[i][j] == 'E' || map->grid[i][j] == 'W')
				if (process_player_character(map, i, j, &found))
					return (1);
			j++;
		}
		i++;
	}
	if (!found)
	{
		ft_putstr_fd("Error\nNo player position\n", 2);
		return (1);
	}
	return (0);
}

static int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ');
}

static int	validate_map_structure(t_map *map)
{
	if (!map || !map->grid || map->height <= 0 || map->width <= 0)
	{
		ft_putstr_fd("Error\nMap structure invalid\n", 2);
		return (1);
	}
	return (0);
}

static int	validate_character_at_position(t_map *map, int i, int j, char c)
{
	int	w;

	w = map->width;
	if (!is_valid_map_char(c))
	{
		ft_putstr_fd("Error\nInvalid character in map\n", 2);
		return (1);
	}
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (i == 0 || j == 0 || i == map->height - 1 || j == w - 1)
		{
			ft_putstr_fd("Error\nMap not closed\n", 2);
			return (1);
		}
		if (map->grid[i - 1][j] == ' ' || map->grid[i + 1][j] == ' '
			|| map->grid[i][j - 1] == ' ' || map->grid[i][j + 1] == ' ')
		{
			ft_putstr_fd("Error\nMap not closed\n", 2);
			return (1);
		}
	}
	return (0);
}

static int	validate_map(t_map *map)
{
	char	c;
	int		i;
	int		j;
	int		w;

	if (validate_map_structure(map))
		return (1);
	i = 0;
	while (i < map->height)
	{
		w = map->width;
		j = 0;
		while (j < w)
		{
			c = map->grid[i][j];
			if (validate_character_at_position(map, i, j, c))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	check_player_position(t_map *map)
{
	if (map->player_x < 0 || map->player_x >= map->width || map->player_y < 0
		|| map->player_y >= map->height)
	{
		ft_putstr_fd("Error\nPlayer position out of map bounds\n", 2);
		return (1);
	}
	return (0);
}

static char	*find_map_start_ptr(char *file_content)
{
	char	*map_start_ptr;

	map_start_ptr = file_content;
	while (*map_start_ptr)
	{
		while (*map_start_ptr == ' ' || *map_start_ptr == '\t')
			map_start_ptr++;
		if (*map_start_ptr == '1' || *map_start_ptr == '0')
			break ;
		while (*map_start_ptr && *map_start_ptr != '\n')
			map_start_ptr++;
		if (*map_start_ptr == '\n')
			map_start_ptr++;
	}
	if (*map_start_ptr == '\0')
		return (NULL);
	return (map_start_ptr);
}

static int	line_has_map_chars(char *line_start, char *line_end)
{
	char	*check_ptr;

	check_ptr = line_start;
	while (check_ptr < line_end)
	{
		if (*check_ptr == '1' || *check_ptr == '0' || *check_ptr == 'N'
			|| *check_ptr == 'S' || *check_ptr == 'E' || *check_ptr == 'W')
			return (1);
		check_ptr++;
	}
	return (0);
}

static char	*find_last_valid_line(char *map_start_ptr)
{
	char	*temp_ptr;
	char	*temp_line_start;
	char	*last_valid_line;

	last_valid_line = NULL;
	temp_ptr = map_start_ptr;
	temp_line_start = temp_ptr;
	while (*temp_ptr)
	{
		if (*temp_ptr == '\n')
		{
			if (line_has_map_chars(temp_line_start, temp_ptr))
				last_valid_line = temp_ptr;
			temp_ptr++;
			temp_line_start = temp_ptr;
		}
		else
			temp_ptr++;
	}
	return (last_valid_line);
}

static int	is_line_empty(char *line_start, char *line_end)
{
	char	*check_ptr;

	check_ptr = line_start;
	while (check_ptr < line_end)
	{
		if (*check_ptr != ' ' && *check_ptr != '\t')
			return (0);
		check_ptr++;
	}
	return (1);
}

static int	validate_map_content(char *map_start_ptr, char *last_valid_line)
{
	char	*line_start;

	line_start = map_start_ptr;
	while (*map_start_ptr && (last_valid_line == NULL
			|| map_start_ptr <= last_valid_line))
	{
		if (*map_start_ptr == '\n')
		{
			if (is_line_empty(line_start, map_start_ptr))
			{
				ft_putstr_fd("Error\nEmpty line inside map\n", 2);
				return (1);
			}
			map_start_ptr++;
			line_start = map_start_ptr;
		}
		else
			map_start_ptr++;
	}
	return (0);
}

static int	check_empty_lines_in_map(char *file_content)
{
	char	*map_start_ptr;
	char	*last_valid_line;

	map_start_ptr = find_map_start_ptr(file_content);
	if (!map_start_ptr)
		return (0);
	last_valid_line = find_last_valid_line(map_start_ptr);
	return (validate_map_content(map_start_ptr, last_valid_line));
}

static char	**prepare_file_content(char *filename)
{
	char	*str;
	char	**tab;

	str = input_to_str(filename);
	if (!str)
	{
		ft_putstr_fd("Error\nFailed to read file\n", 2);
		return (NULL);
	}
	if (check_empty_lines_in_map(str))
	{
		free(str);
		return (NULL);
	}
	tab = ft_split(str, '\n');
	free(str);
	if (!tab)
	{
		ft_putstr_fd("Error\nFailed to split file\n", 2);
		return (NULL);
	}
	return (tab);
}

static int	validate_required_fields(t_fields *fields, char **tab)
{
	if (!fields->no_filename || !fields->so_filename || !fields->we_filename
		|| !fields->ea_filename || fields->floor[0] == -1
		|| fields->core[0] == -1)
	{
		ft_putstr_fd("Error\nMissing required field(s)\n", 2);
		free_strs(tab);
		return (1);
	}
	return (0);
}

static int	validate_final_map(t_fields *fields, char **tab)
{
	if (find_player_in_map(fields->map))
		return (1);
	if (check_player_position(fields->map))
		return (1);
	if (validate_map(fields->map))
	{
		free_strs(tab);
		return (1);
	}
	return (0);
}

int	parse(char *filename, t_fields *fields)
{
	char	**tab;
	int		map_start;

	tab = prepare_file_content(filename);
	if (!tab)
		return (1);
	if (parse_fields(tab))
	{
		free_strs(tab);
		return (1);
	}
	map_start = fill_fields_from_lines(tab, fields);
	if (validate_required_fields(fields, tab))
		return (1);
	if (fill_map_from_lines(tab, map_start, fields))
	{
		free_strs(tab);
		ft_putstr_fd("Error\nFailed to parse map\n", 2);
		return (1);
	}
	if (validate_final_map(fields, tab))
		return (1);
	free_strs(tab);
	return (0);
}

void	fill_texture(char **dest, char *src)
{
	if (*dest)
		free(*dest);
	while (*src == ' ' || *src == '\t')
		src++;
	*dest = ft_strdup(src);
}

static int	check_comma_validity(char *str, int i, int comma_count)
{
	if (i == 0 || str[i - 1] == ',' || str[i + 1] == ',' || str[i + 1] == '\0')
	{
		ft_putstr_fd("Error\nInvalid color format: comma\n", 2);
		exit(1);
	}
	return (comma_count + 1);
}

static void	validate_character(char c, int i, char *str, int *comma_count)
{
	if (c == ',')
		*comma_count = check_comma_validity(str, i, *comma_count);
	else if (c < '0' || c > '9')
	{
		ft_putstr_fd("Error\nColor components must be numeric\n", 2);
		exit(1);
	}
}

static int	validate_color_format(char *str)
{
	int	i;
	int	comma_count;

	comma_count = 0;
	i = 0;
	while (str[i])
	{
		validate_character(str[i], i, str, &comma_count);
		i++;
	}
	if (comma_count != 2)
	{
		ft_putstr_fd("Error\nColor must have exactly 3 values (R,G,B)\n", 2);
		exit(1);
	}
	return (0);
}

static void	process_color_values(int *color, char **rgb)
{
	int	i;
	int	val;

	i = 0;
	while (i < 3)
	{
		val = ft_atoi(rgb[i]);
		if (val < 0 || val > 255)
		{
			ft_putstr_fd("Error\nColor value must be between 0 and 255\n", 2);
			free_strs(rgb);
			exit(1);
		}
		color[i] = val;
		i++;
	}
}

void	fill_color(int *color, char *str)
{
	char	**rgb;

	while (*str == ' ' || *str == '\t')
		str++;
	validate_color_format(str);
	rgb = ft_split(str, ',');
	if (!rgb)
	{
		ft_putstr_fd("Error\nInvalid color format\n", 2);
		exit(1);
	}
	process_color_values(color, rgb);
	free_strs(rgb);
}

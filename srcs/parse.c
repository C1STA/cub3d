/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 04:30:00 by dpinto            #+#    #+#             */
/*   Updated: 2025/07/09 02:29:55 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

/*
** Détecte si une ligne est le début de la map (ignore espaces/tabs)
*/
int	is_map_line(const char *line)
{
	int	j;

	j = 0;
	while (line[j] && (line[j] <= 32))
		j++;
	return (line[j] == '1' || line[j] == '0');
}

/*
** Parsing des champs avant la map,
	gestion des doublons et identifiants invalides
*/
int	parse_fields(char **tab)
{
	int			found[6] = {0, 0, 0, 0, 0, 0};
	const char	*f[6] = {"NO", "SO", "WE", "EA", "F", "C"};

	int i, j, k, len, is_valid;
	i = 0;
	while (tab[i])
	{
		k = 0;
		while (tab[i][k] && (tab[i][k] <= 32))
			k++;
		if (is_map_line(tab[i]))
			break ;
		if (ft_strlen(tab[i] + k) > 0)
		{
			is_valid = 0;
			j = 0;
			while (j < 6)
			{
				len = ft_strlen(f[j]);
				if (!ft_strncmp(tab[i] + k, f[j], len) && (tab[i][k
						+ len] == ' ' || tab[i][k + len] == '\t'))
				{
					if (found[j])
					{
						ft_putstr_fd("Error\nDuplicate identifier\n", 2);
						return (1);
					}
					found[j] = 1;
					is_valid = 1;
				}
				j++;
			}
			if (!is_valid)
			{
				ft_putstr_fd("Error\nInvalid identifier\n", 2);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

/* Fonction pour vérifier si une ligne est vide ou ne contient que des espaces */
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

/* Remplit la structure fields à partir des lignes du fichier .cub */
static int	fill_fields_from_lines(char **tab, t_fields *fields)
{
	const char	*f[6] = {"NO", "SO", "WE", "EA", "F", "C"};

	int i, k, len;
	i = 0;
	while (tab[i])
	{
		k = 0;
		while (tab[i][k] && (tab[i][k] <= 32))
			k++;
		if (is_map_line(tab[i]))
			break ;
		if (ft_strlen(tab[i] + k) > 0)
		{
			if (!ft_strncmp(tab[i] + k, f[0], 2))
				fill_texture(&fields->no_filename, tab[i] + k + 2);
			else if (!ft_strncmp(tab[i] + k, f[1], 2))
				fill_texture(&fields->so_filename, tab[i] + k + 2);
			else if (!ft_strncmp(tab[i] + k, f[2], 2))
				fill_texture(&fields->we_filename, tab[i] + k + 2);
			else if (!ft_strncmp(tab[i] + k, f[3], 2))
				fill_texture(&fields->ea_filename, tab[i] + k + 2);
			else if (!ft_strncmp(tab[i] + k, f[4], 1))
				fill_color(fields->floor, tab[i] + k + 1);
			else if (!ft_strncmp(tab[i] + k, f[5], 1))
				fill_color(fields->core, tab[i] + k + 1);
		}
		i++;
	}
	return (i); // retourne l'index du début de la map
}

/* Remplit la structure map à partir des lignes de la map dans le fichier .cub */
static int	fill_map_from_lines(char **tab, int map_start, t_fields *fields)
{
	char	*padded;
	int		map_started;

	int i, j, height, max_width, len;
	map_started = 0;
	height = 0;
	max_width = 0;
	i = map_start;
	while (tab[i])
	{
		len = ft_strlen(tab[i]);
		if (len > 0 && !is_empty_line(tab[i]))
		{
			if (len > max_width)
				max_width = len;
			height++;
			map_started = 1;
		}
		else if (map_started && (len == 0 || is_empty_line(tab[i])))
		{
			// Ligne vide détectée après le début de la carte
			ft_putstr_fd("Error\nEmpty line inside map\n", 2);
			return (1);
		}
		i++;
	}
	if (height == 0)
		return (1);
	fields->map = malloc(sizeof(t_map));
	if (!fields->map)
		return (1);
	fields->map->grid = malloc(sizeof(char *) * (height + 1));
	if (!fields->map->grid)
		return (1);
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
	fields->map->height = height;
	fields->map->width = max_width;
	return (0);
}

/* Détecte et stocke la position du joueur dans la map */
static int	find_player_in_map(t_map *map)
{
	int i, j, found;
	found = 0;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (map->grid[i][j] == 'N' || map->grid[i][j] == 'S'
				|| map->grid[i][j] == 'E' || map->grid[i][j] == 'W')
			{
				if (found)
				{
					ft_putstr_fd("Error\nMultiple player positions\n", 2);
					return (1);
				}
				map->player_x = j;
				map->player_y = i;
				map->player_dir = map->grid[i][j];
				map->grid[i][j] = '0';
				found = 1;
			}
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

static int	validate_map(t_map *map)
{
	char	c;

	int i, j, w;
	if (!map || !map->grid || map->height <= 0 || map->width <= 0)
	{
		ft_putstr_fd("Error\nMap structure invalid\n", 2);
		return (1);
	}
	i = 0;
	while (i < map->height)
	{
		w = map->width;
		j = 0;
		while (j < w)
		{
			c = map->grid[i][j];
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
			j++;
		}
		i++;
	}
	return (0);
}

// Ajoutons une fonction de sécurité pour la position du joueur
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

/* Fonction pour détecter les lignes vides dans la section map du fichier original */
static int	check_empty_lines_in_map(char *file_content)
{
	char	*map_start_ptr;
	char	*line_start;
	char	*last_valid_line;
	char	*temp_ptr;
	char	*temp_line_start;
	char	*check_ptr;
	int		in_map_section;
	int		map_started;
	int		has_map_chars;
	int		is_empty;

	in_map_section = 0;
	map_started = 0;
	last_valid_line = NULL;
	// Trouver le début de la section map
	map_start_ptr = file_content;
	while (*map_start_ptr)
	{
		// Ignorer les espaces au début de la ligne
		while (*map_start_ptr == ' ' || *map_start_ptr == '\t')
			map_start_ptr++;
		if (*map_start_ptr == '1' || *map_start_ptr == '0')
		{
			in_map_section = 1;
			map_started = 1;
			break ;
		}
		// Passer à la ligne suivante
		while (*map_start_ptr && *map_start_ptr != '\n')
			map_start_ptr++;
		if (*map_start_ptr == '\n')
			map_start_ptr++;
	}
	if (!in_map_section)
		return (0); // Pas de map trouvée
	// D'abord, trouver la dernière ligne valide de la carte
	temp_ptr = map_start_ptr;
	temp_line_start = temp_ptr;
	while (*temp_ptr)
	{
		if (*temp_ptr == '\n')
		{
			// Vérifier si cette ligne contient des caractères de carte valides
			check_ptr = temp_line_start;
			has_map_chars = 0;
			while (check_ptr < temp_ptr)
			{
				if (*check_ptr == '1' || *check_ptr == '0' || *check_ptr == 'N'
					|| *check_ptr == 'S' || *check_ptr == 'E'
					|| *check_ptr == 'W')
				{
					has_map_chars = 1;
					break ;
				}
				check_ptr++;
			}
			if (has_map_chars)
				last_valid_line = temp_ptr;
			// Marquer cette position comme dernière ligne valide
			temp_ptr++;
			temp_line_start = temp_ptr;
		}
		else
		{
			temp_ptr++;
		}
	}
	// Maintenant analyser seulement jusqu'à la dernière ligne valide
	line_start = map_start_ptr;
	while (*map_start_ptr && (last_valid_line == NULL
			|| map_start_ptr <= last_valid_line))
	{
		if (*map_start_ptr == '\n')
		{
			// Vérifier si la ligne est vide ou ne contient que des espaces
			check_ptr = line_start;
			is_empty = 1;
			while (check_ptr < map_start_ptr)
			{
				if (*check_ptr != ' ' && *check_ptr != '\t')
				{
					is_empty = 0;
					break ;
				}
				check_ptr++;
			}
			if (is_empty && map_started)
			{
				ft_putstr_fd("Error\nEmpty line inside map\n", 2);
				return (1);
			}
			// Passer à la ligne suivante
			map_start_ptr++;
			line_start = map_start_ptr;
		}
		else
		{
			map_start_ptr++;
		}
	}
	return (0);
}

/*
** Fonction principale de parsing (à compléter selon la structure du projet)
*/
int	parse(char *filename, t_fields *fields)
{
	char	*str;
	char	**tab;
	int		map_start;

	str = input_to_str(filename);
	if (!str)
	{
		ft_putstr_fd("Error\nFailed to read file\n", 2);
		return (1);
	}
	// Vérifier les lignes vides dans la map AVANT de diviser le string
	if (check_empty_lines_in_map(str))
	{
		free(str);
		return (1);
	}
	tab = ft_split(str, '\n');
	free(str);
	if (!tab)
	{
		ft_putstr_fd("Error\nFailed to split file\n", 2);
		return (1);
	}
	if (parse_fields(tab))
	{
		free_strs(tab);
		return (1);
	}
	map_start = fill_fields_from_lines(tab, fields);
	// AJOUT: Vérification que tous les champs obligatoires sont présents
	if (!fields->no_filename || !fields->so_filename || !fields->we_filename
		|| !fields->ea_filename || fields->floor[0] == -1 || fields->core[0] ==
		-1)
	{
		ft_putstr_fd("Error\nMissing required field(s)\n", 2);
		free_strs(tab);
		return (1);
	}
	if (fill_map_from_lines(tab, map_start, fields))
	{
		free_strs(tab);
		ft_putstr_fd("Error\nFailed to parse map\n", 2);
		return (1);
	}
	if (find_player_in_map(fields->map))
		return (1);
	if (check_player_position(fields->map))
		return (1);
	if (validate_map(fields->map))
	{
		free_strs(tab);
		return (1);
	}
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

void	fill_color(int *color, char *str)
{
	char **rgb;
	int i;
	int val;
	int comma_count;

	while (*str == ' ' || *str == '\t')
		str++;

	// Valider le format de la chaîne AVANT ft_split
	comma_count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
		{
			comma_count++;
			// Vérifier les virgules doubles
			if (i == 0 || str[i - 1] == ',' || str[i + 1] == ',' || str[i
				+ 1] == '\0')
			{
				ft_putstr_fd("Error\nInvalid color format: double comma or comma at start/end\n",
					2);
				exit(1);
			}
		}
		else if (str[i] < '0' || str[i] > '9')
		{
			ft_putstr_fd("Error\nColor components must be numeric\n", 2);
			exit(1);
		}
		i++;
	}

	// Vérifier qu'il y a exactement 2 virgules (pour 3 composantes)
	if (comma_count != 2)
	{
		ft_putstr_fd("Error\nColor must have exactly 3 values (R,G,B)\n", 2);
		exit(1);
	}

	rgb = ft_split(str, ',');
	if (!rgb)
	{
		ft_putstr_fd("Error\nInvalid color format\n", 2);
		exit(1);
	}

	// À ce point, nous savons qu'il y a exactement 3 composantes
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
	free_strs(rgb);
}
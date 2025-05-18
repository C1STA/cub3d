/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 23:28:45 by dpinto            #+#    #+#             */
/*   Updated: 2025/05/18 06:22:41 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	fill_fields(t_fields *fields, char **raws, const char *field)
{
	char	**tmpTab;

	if (field == "NO")
		fields->no_filename = ft_strdup(raws[1]);
	else if (field == "SO")
		fields->so_filename = ft_strdup(raws[1]);
	else if (field == "WE")
		fields->we_filename = ft_strdup(raws[1]);
	else if (field == "EA")
		fields->ea_filename = ft_strdup(raws[1]);
	else if (field == "F")
	{
		tmpTab = ft_split(raws[1], ',');
		fields->floor[0] = ft_atoi(tmpTab[0]);
		fields->floor[1] = ft_atoi(tmpTab[1]);
		fields->floor[2] = ft_atoi(tmpTab[2]);
		free_strs(tmpTab);
	}
	else if (field == "C")
	{
		tmpTab = ft_split(raws[1], ',');
		fields->core[0] = ft_atoi(tmpTab[0]);
		fields->core[1] = ft_atoi(tmpTab[1]);
		fields->core[2] = ft_atoi(tmpTab[2]);
		free_strs(tmpTab);
	}
}

static int	fields_is_present(char **tab, const char *field, t_fields *fields)
{
	char	**raws;
	int		i;

	i = 0;
	while (i < 6)
	{
		if (!ft_strncmp(tab[i], field, ft_strlen(field)))
		{
			raws = ft_split(tab[i], ' ');
			if (raws == NULL)
				return (0);
			if (get_tab_len(raws) != 2)
				return (0);
			fill_fields(fields, raws, field);
			free_strs(raws);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_required_field(char **tab, t_fields *fields)
{
	int			i;
	const char	*f[6] = {"NO", "SO", "WE", "EA", "F", "C"};

	i = 0;
	while (i < 6)
	{
		if (!fields_is_present(tab, f[i], fields))
			return (1);
		i++;
	}
	return (0);
}

int	parse(char *filename, t_fields *fields)
{
	char	*str;
	char	**tab;

	if (check_ext(filename))
	{
		ft_putstr_fd("Error\nWrong extension !\n", 2);
		return (1);
	}
	str = input_to_str(filename);
	if (str == NULL)
		return (1);
	tab = ft_split(str, '\n');
	if (tab == NULL)
		return (1);
	free(str);
	if (check_required_field(tab, fields))
		ft_putstr_fd("Error\nFields missing !\n", 2);
	free_strs(tab);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 02:14:43 by dpinto            #+#    #+#             */
/*   Updated: 2025/05/18 02:32:16 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char	*input_to_str(char *filename)
{
	int		fd;
	int		count;
	char	buf[50];
	char	*str;
	char	*tmp;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error\nfailed to open file\n", 2), NULL);
	str = ft_strdup("\0");
	if (str == NULL)
		return (NULL);
	count = 1;
	while (count != 0)
	{
		count = read(fd, buf, 49);
		if (count == -1)
			return (free(str), NULL);
		buf[count] = '\0';
		tmp = str;
		str = ft_strjoin(str, buf);
		free(tmp);
	}
	close(fd);
	return (str);
}

int	check_ext(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (1);
	if (ft_strncmp(filename + (len - 4), ".cub", 4) != 0)
		return (1);
	if (ft_strncmp(filename + (len - 5), "/.cub", 5) == 0)
		return (1);
	return (0);
}

size_t	get_tab_len(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}

char	**free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

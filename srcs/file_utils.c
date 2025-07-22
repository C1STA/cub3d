/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:42:45 by dpinto            #+#    #+#             */
/*   Updated: 2025/05/26 02:02:34 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static char	*read_file_content(int fd, char *str)
{
	int		count;
	char	buf[50];
	char	*tmp;

	count = 1;
	while (count > 0)
	{
		count = read(fd, buf, 49);
		if (count == -1)
			return (free(str), ft_putstr_fd("Error\n\
Failed to read file\n", 2), NULL);
		buf[count] = '\0';
		tmp = str;
		str = ft_strjoin(str, buf);
		free(tmp);
		if (count == 0 && !*str)
		{
			if (str)
				free(str);
			return (ft_putstr_fd("Error\nFile is empty\n", 2), NULL);
		}
		if (!str)
			return (ft_putstr_fd("Error\nAllocation failed\n", 2), NULL);
	}
	return (str);
}

char	*input_to_str(char *filename)
{
	int		fd;
	char	*str;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error\nFailed to open file\n", 2), NULL);
	str = ft_strdup("");
	if (!str)
		return (close(fd), ft_putstr_fd("Error\nAllocation failed\n", 2), NULL);
	str = read_file_content(fd, str);
	close(fd);
	return (str);
}

int	check_ext(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (1);
	return (ft_strncmp(filename + len - 4, ".cub", 4));
}

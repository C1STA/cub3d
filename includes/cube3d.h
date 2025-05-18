/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 01:34:38 by dpinto            #+#    #+#             */
/*   Updated: 2025/05/18 06:15:08 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <libft.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

typedef struct s_fields
{
	char	*no_filename;
	char	*so_filename;
	char	*we_filename;
	char	*ea_filename;
	int		core[3];
	int		floor[3];

}			t_fields;

void		print_fields(t_fields *fields);

size_t		get_tab_len(char **tab);
char		**free_strs(char **strs);
int			check_ext(char *filename);
char		*input_to_str(char *filename);

int			parse(char *str, t_fields *f);

#endif

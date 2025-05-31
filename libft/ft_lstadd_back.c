/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 00:45:24 by dpinto            #+#    #+#             */
/*   Updated: 2025/05/31 05:03:58 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *node)
{
	t_list	*ptr;

	ptr = *lst;
	if (ptr == NULL)
	{
		*lst = node;
		return ;
	}
	while (ptr != NULL)
	{
		if (ptr->next == NULL)
		{
			ptr->next = node;
			break ;
		}
		ptr = ptr->next;
	}
}

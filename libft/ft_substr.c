/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <pintodav75@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 02:19:03 by dpinto            #+#    #+#             */
/*   Updated: 2024/04/19 04:02:23 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strncpy(char *dest, char const *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	dest[i] = 0;
	return (dest);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	str_len;
	char	*res;

	if (!s || start > ft_strlen(s))
		return (ft_strdup(""));
	str_len = ft_strlen(s + start);
	if (str_len > len)
		str_len = len;
	res = (char *)malloc(sizeof(char) * (str_len + 1));
	if (res == NULL)
		return (res);
	ft_strncpy(res, s + start, str_len);
	return (res);
}

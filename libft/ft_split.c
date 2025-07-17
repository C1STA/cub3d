/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 23:17:30 by dpinto            #+#    #+#             */
/*   Updated: 2024/06/12 23:22:02 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_free(char **tab, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static int	get_tab_len(const char *str, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str && str[i] != '\0')
	{
		if (str[i] != c)
		{
			words++;
			while (str[i] != '\0' && str[i] != c)
				i++;
		}
		if (str[i] == '\0')
			return (words);
		i++;
	}
	return (words);
}

static char	*ft_strndup(const char *str, int word_len)
{
	char	*dest;
	int		i;

	dest = (char *)malloc(sizeof(char) * (word_len + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (i < word_len)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	**fill_tab(const char *str, char c, char **tab)
{
	int	i;
	int	word_len;
	int	k;

	i = 0;
	k = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			word_len = 0;
			while (str[i] != c && str[i] != '\0')
			{
				word_len++;
				i++;
			}
			tab[k] = ft_strndup(str + i - word_len, word_len);
			if (tab[k] == NULL)
				return (ft_free(tab, k));
			k++;
		}
		else
			i++;
	}
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		tab_len;

	if (!s)
		return (NULL);
	tab_len = get_tab_len(s, c) + 1;
	tab = (char **)malloc(sizeof(char *) * (tab_len));
	if (tab == NULL)
		return (NULL);
	tab[tab_len - 1] = NULL;
	if (!s)
		return (tab);
	return (fill_tab(s, c, tab));
}

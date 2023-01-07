/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 17:17:14 by rapdos-s          #+#    #+#             */
/*   Updated: 2022/07/13 12:19:13 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Insert the strings from 's' delimited by 'c' in preview allocated '
 * list'.
 * 
 * @param list Preview allocated array of strings.
 * @param s String to be splitted.
 * @param c Delimiter.
 */
static void	ft_insertstr(char **list, char const *s, char c)
{
	size_t	i;
	size_t	len;
	size_t	start;

	i = 0;
	len = 0;
	start = 0;
	while (s[start + len])
	{
		while (s[start] == c && s[start])
			start++;
		while (s[start + len] != c && s[start + len])
			len++;
		if (len)
		{
			list[i] = ft_substr(s, start, len);
			start = start + len;
			len = 0;
			i++;
		}
	}
	list[i] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**list;
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c && i != 0 && s[i - 1] != c)
			count++;
		i++;
	}
	if (i != 0 && s[i - 1] != c && ft_strlen(s) > 0)
		count++;
	list = malloc(sizeof(char *) * (count + 1));
	if (!list)
		return (NULL);
	ft_insertstr(list, s, c);
	return (list);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 18:01:53 by rabustam          #+#    #+#             */
/*   Updated: 2022/11/18 19:53:01 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_strs(const char *s, char c)
{
	int		count;
	int		split;
	size_t	i;

	i = 0;
	count = 0;
	split = 0;
	while (s[i])
	{
		if (s[i] != c && split == 0)
		{
			split = 1;
			count++;
		}
		else if (s[i] == c)
			split = 0;
		i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	size_t	i;
	size_t	j;
	int		index;

	strs = malloc((ft_count_strs(s, c) + 1) * sizeof(char *));
	if (!strs)
		return (0);
	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if ((s[i] != c && s[i] != '\0') && index < 0)
			index = i;
		if ((s[i] == c || s[i] == '\0') && index >= 0)
		{
			strs[j] = ft_substr(s, index, (i - index));
			j++;
			index = -1;
		}
		i++;
	}
	strs[j] = 0;
	return (strs);
}

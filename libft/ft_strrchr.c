/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:41:47 by rabustam          #+#    #+#             */
/*   Updated: 2022/06/09 19:24:26 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	while (c > 255)
		c = c - 256;
	i = 0;
	while (s[i])
		i++;
	while (&s[i] >= &s[0])
	{
		if (s[i] == c)
			return ((char *)(&s[i]));
		i--;
	}
	return (0);
}

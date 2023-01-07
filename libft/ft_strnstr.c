/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 17:09:28 by rapdos-s          #+#    #+#             */
/*   Updated: 2022/06/28 10:56:10 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*big_cpy;
	size_t	little_len;
	size_t	i;

	big_cpy = (char *)big;
	little_len = ft_strlen(little);
	i = 0;
	if (!*little)
		return (big_cpy);
	while (big[i] && i < len)
	{
		if (!ft_strncmp(&big[i], little, little_len) && (i + little_len <= len))
			return (&big_cpy[i]);
		i++;
	}
	return (NULL);
}

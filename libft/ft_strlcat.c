/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 19:29:42 by rapdos-s          #+#    #+#             */
/*   Updated: 2022/06/26 21:31:30 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_len;

	i = 0;
	dest_len = 0;
	while (dest[dest_len] && dest_len < size)
		dest_len++;
	i = dest_len;
	while (src[i - dest_len] && (i + 1) < size)
	{
		dest[i] = src[i - dest_len];
		i++;
	}
	if (dest_len < size)
		dest[i] = 0;
	return (dest_len + ft_strlen(src));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 22:12:33 by rapdos-s          #+#    #+#             */
/*   Updated: 2022/07/13 01:41:09 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*u_src;
	unsigned char	*u_dest;

	if (dest == NULL && src == NULL)
		return (NULL);
	u_src = (unsigned char *)src;
	u_dest = (unsigned char *)dest;
	while (n--)
		u_dest[n] = u_src[n];
	return (dest);
}

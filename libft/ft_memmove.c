/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 01:24:40 by rabustam          #+#    #+#             */
/*   Updated: 2022/06/08 22:07:25 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const void	*s;
	void		*d;

	if (src < dest && dest < src + n)
	{
		while (n--)
		{
			d = dest + n;
			s = src + n;
			*(char *)d = *(char *)s;
		}
		return (d);
	}
	return (ft_memcpy(dest, src, n));
}

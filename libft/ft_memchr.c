/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 16:30:21 by rapdos-s          #+#    #+#             */
/*   Updated: 2022/07/06 22:33:49 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*uc_s;

	uc_s = (unsigned char *) s;
	while (n--)
	{
		if (*uc_s == (unsigned char) c)
			return (uc_s);
		uc_s++;
	}
	return (NULL);
}

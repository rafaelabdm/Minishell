/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 00:55:32 by rapdos-s          #+#    #+#             */
/*   Updated: 2022/07/13 01:48:14 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Count the number of digits of the int 'n'.
 * 
 * @param n Integer that will have its 'digits' counted.
 * @return Number of digits.
 */
static int	ft_nbrlen(int n)
{
	int	digits;

	digits = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		digits++;
	while (n)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

/**
 * @brief Convert a each digit of integer 'n' with 'digits' digits and copy to
 * the previews allocated string 's'.
 * 
 * @param s String were the digits will be allocated.
 * @param n Integer to be converted.
 * @param digits Number of digits of 'n'.
 */
static void	ft_convert(char *s, int n, int digits)
{
	unsigned int	u_n;

	if (n == 0)
		s[0] = '0';
	if (n < 0)
	{
		s[0] = '-';
		u_n = -n;
	}
	else
		u_n = n;
	while (u_n)
	{
		s[digits] = u_n % 10 + '0';
		u_n /= 10;
		digits--;
	}
}

char	*ft_itoa(int n)
{
	char	*s;
	int		digits;

	digits = ft_nbrlen(n);
	s = ft_calloc((digits + 1), sizeof(char));
	if (!s)
		return (NULL);
	ft_convert(s, n, digits - 1);
	return (s);
}

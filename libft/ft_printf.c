/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 00:10:51 by rapdos-s          #+#    #+#             */
/*   Updated: 2022/09/07 17:16:52 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Print a string and return the printed amount.
 * 
 * @param s String to be printed.
 * @return Number of printed characters.
 */
static int	ft_print_txt(const char *s)
{
	int	str_len;

	str_len = 0;
	if (s == NULL)
		return (write (1, "(null)", 6));
	else
		while (s[str_len])
			str_len++;
	return (write (1, s, str_len));
}

/**
 * @brief Print a number and return the number of printed characters.
 * 
 * @param n Number to be printed.
 * @param specifier 'd' or 'i' for integer numbers, 'p' for memory address and
 * 'x' or 'X' for hexadecimals numbers.
 * @param base '10' for decimal and '16' for hexadecimal.
 * @return Number of printed characters.
 */
static int	ft_print_nbr(long n, char specifier, unsigned long base)
{
	unsigned long	u_n;
	int				print_count;
	char			digit;

	print_count = 0;
	if (n < 0 && (specifier == 'd' || specifier == 'i'))
		print_count += write (1, "-", 1);
	if (specifier == 'p')
	{
		if (n == 0)
			return (write (1, "(nil)", 5));
		u_n = (unsigned long) n;
		print_count = ft_print_txt ("0x");
		specifier = 'x';
	}
	else
		u_n = n * (-(n < 0) + (n > 0));
	if (u_n >= base)
		print_count += ft_print_nbr (u_n / base, specifier, base);
	if (u_n % base >= 10)
		digit = u_n % base - 10 + 'a' - (32 * (specifier == 'X'));
	else
		digit = u_n % base + '0';
	print_count += write (1, &digit, 1);
	return (print_count);
}

/**
 * @brief Select the appropriate function for the current specifier in 's' to
 * print the current 'arg' var.
 * 
 * @param s Pointer to the current specifier
 * @param args A va_list pointing to the current var to be printed.
 * @return Number of printed characters.
 */
static int	call_specifier(const char *s, va_list args)
{
	int		count;
	char	c;

	if (*s == 'c')
	{
		c = va_arg (args, int);
		count = write (1, &c, 1);
	}
	else if (*s == 's')
		count = ft_print_txt (va_arg (args, char *));
	else if (*s == 'p')
		count = ft_print_nbr ((long) va_arg (args, unsigned long), *s, 16);
	else if (*s == 'd' || *s == 'i')
		count = ft_print_nbr ((long) va_arg (args, int), *s, 10);
	else if (*s == 'u')
		count = ft_print_nbr ((long) va_arg (args, unsigned int), *s, 10);
	else if (*s == 'x' || *s == 'X')
		count = ft_print_nbr ((long) va_arg (args, unsigned int), *s, 16);
	else
		count = write (1, s, 1);
	return (count);
}

int	ft_printf(const char *s, ...)
{
	int		print_count;
	int		temp_count;
	va_list	args;

	va_start (args, s);
	print_count = 0;
	temp_count = 0;
	while (*s && temp_count != -1)
	{
		print_count += temp_count;
		if (*s != '%')
			temp_count = write (1, s, 1);
		else
			temp_count = call_specifier (++s, args);
		s++;
	}
	if (temp_count == -1)
		print_count = temp_count;
	else
		print_count += temp_count;
	va_end (args);
	return (print_count);
}

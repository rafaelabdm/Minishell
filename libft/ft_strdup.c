/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 17:10:31 by rapdos-s          #+#    #+#             */
/*   Updated: 2022/07/13 01:37:28 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*s_dup;

	if (!s)
		return (NULL);
	s_dup = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!s_dup)
		return (NULL);
	ft_strlcpy(s_dup, s, (ft_strlen(s) + 1));
	return (s_dup);
}

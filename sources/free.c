/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 17:21:08 by rapdos-s          #+#    #+#             */
/*   Updated: 2022/11/27 17:21:08 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*free_ptr(char *ptr)
{
	free(ptr);
	ptr = NULL;
	return (NULL);
}

char	**free_mat(char **mat)
{
	size_t	i;

	i = 0;
	while (mat && mat[i])
	{
		mat[i] = free_ptr(mat[i]);
		i++;
	}
	free (mat);
	mat = NULL;
	return (NULL);
}

t_token	*free_token(t_token *token)
{
	t_token	*temp;

	while (token)
	{
		temp = token;
		token -> cmd = free_ptr (token -> cmd);
		token = token -> next;
		free (temp);
	}
	return (NULL);
}

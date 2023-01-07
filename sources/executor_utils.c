/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:10:02 by rabustam          #+#    #+#             */
/*   Updated: 2023/01/03 14:10:02 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**token_to_mat(t_token *token)
{
	int		i;
	int		j;
	char	**ret;
	t_token	*temp;

	temp = token;
	i = 0;
	while (temp && temp->type != PIPE)
	{
		i++;
		temp = temp->next;
	}
	ret = ft_calloc((i + 1), sizeof(char *));
	if (!ret)
		return (NULL);
	j = -1;
	while (++j < i)
	{
		ret[j] = ft_strdup(token->cmd);
		token = token->next;
	}
	ret[j] = NULL;
	return (ret);
}

void	close_fds(int **fd)
{
	int	i;

	i = 0;
	while (fd[i])
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

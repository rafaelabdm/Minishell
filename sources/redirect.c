/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 09:40:51 by rabustam          #+#    #+#             */
/*   Updated: 2022/12/28 09:40:51 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_fd(int	*fd)
{
	fd[0] = -1;
	fd[1] = -1;
}

char	**redirect(t_mini *ms, char **cmd, int *out, int *in)
{
	int		fd[2];
	char	**ret;
	int		i;

	init_fd(fd);
	i = 0;
	while (cmd[i])
		i++;
	ret = ft_calloc(i + 1, sizeof(char *));
	set_redirect(ms, cmd, fd, ret);
	if (fd[0] == -5 || fd[1] == -5)
		return (free_mat(ret));
	if (fd[0] != -1)
	{
		dup2(fd[0], 0);
		close(fd[0]);
		*in = 1;
	}
	if (fd[1] != -1)
	{
		dup2(fd[1], 1);
		close(fd[1]);
		*out = 1;
	}
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 09:32:59 by rapdos-s          #+#    #+#             */
/*   Updated: 2022/11/27 09:32:59 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_handler(t_mini *ms, const char *msg, const int code)
{
	int	i;

	if (code && code != 127)
		ft_putstr_fd (ERROR_MSG, 2);
	if (msg)
		ft_putendl_fd ((char *) msg, 2);
	if (!code && !msg)
		ft_putendl_fd (EXIT_MSG, 1);
	ms -> input = free_ptr (ms -> input);
	ms -> prompt = free_ptr (ms -> prompt);
	ms -> token = free_token (ms -> token);
	ms -> envp = free_mat (ms -> envp);
	rl_clear_history ();
	unlink("__heredoc");
	i = 0;
	while (!close(i))
		i++;
	exit(code);
}

int	check_quotes(char c, int quotes)
{
	if (c == '\"')
	{
		if (!quotes)
			return (1);
		else if (quotes == 1)
			return (0);
	}
	else if (c == '\'')
	{
		if (!quotes)
			return (2);
		else if (quotes == 2)
			return (0);
	}
	return (quotes);
}

char	*ft_mattstr_copy(char **mat)
{
	char	*str;
	char	*temp;
	int		i;

	str = ft_strdup(mat[0]);
	i = 0;
	while (mat[++i])
	{
		temp = str;
		str = ft_strjoin(temp, mat[i]);
		temp = free_ptr(temp);
	}
	mat = free_mat(mat);
	return (str);
}

char	**ft_matdup(char **mat)
{
	char	**temp;
	size_t	i;

	if (!mat)
		return (NULL);
	i = 0;
	while (mat[i])
		i++;
	temp = ft_calloc (i + 1, sizeof (char *));
	if (!temp)
		return (NULL);
	i = 0;
	while (mat[i])
	{
		temp[i] = ft_strdup (mat[i]);
		i++;
	}
	temp[i] = NULL;
	return (temp);
}

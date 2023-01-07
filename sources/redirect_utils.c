/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 09:56:00 by rabustam          #+#    #+#             */
/*   Updated: 2022/12/28 09:56:00 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	heredoc(t_mini *ms, const char *eof, char **envp)
{
	char	*input;
	int		file;

	input = NULL;
	file = open("__heredoc", O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	while (1)
	{
		input = readline("> ");
		if (!ft_strncmp(eof, input, ft_strlen(input)))
		{
			input = free_ptr(input);
			break ;
		}
		if (*eof != '\'' && *eof != '\"' && ft_strchr(input, '$'))
			input = expand(ms, input, envp);
		write(file, input, ft_strlen(input));
		write(file, "\n", 1);
		input = free_ptr(input);
		input = NULL;
	}
	close(file);
	file = open("__heredoc", O_RDONLY);
	return (file);
}

static int	is_redin(t_mini *ms, char **cmd, int i, char **envp)
{
	static int	file = -1;

	if (!ft_strncmp(cmd[i], "<", 2))
	{
		file = open(cmd[i + 1], O_RDONLY);
		if (file == -1)
			return (-5);
	}
	else if (!ft_strncmp(cmd[i], "<<", 3))
		file = heredoc(ms, cmd[i + 1], envp);
	return (file);
}

static int	is_redout(char **cmd, int i)
{
	static int	file = -1;

	if (!ft_strncmp(cmd[i], ">", 2))
	{
		file = open(cmd[i + 1], O_WRONLY | O_CREAT, 0777);
		if (file == -1)
			return (-5);
	}
	else if (!ft_strncmp(cmd[i], ">>", 3))
	{
		file = open(cmd[i + 1], O_APPEND | O_WRONLY | O_CREAT, 0777);
		if (file == -1)
			return (-5);
	}
	return (file);
}

static int	is_redirect(char *cmd)
{
	if (!ft_strncmp(cmd, ">", 2))
		return (1);
	if (!ft_strncmp(cmd, ">>", 3))
		return (1);
	if (!ft_strncmp(cmd, "<", 2))
		return (1);
	if (!ft_strncmp(cmd, "<<", 3))
		return (1);
	return (0);
}

void	set_redirect(t_mini *ms, char **cmd, int *fd, char **ret)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (is_redirect(cmd[i]))
		{
			fd[0] = is_redin(ms, cmd, i, ms->envp);
			fd[1] = is_redout(cmd, i);
			i = i + 2;
			if (fd[0] == -5 || fd[1] == -5)
				break ;
		}
		else
			ret[j++] = ft_strdup(cmd[i++]);
	}
	cmd = free_mat(cmd);
}

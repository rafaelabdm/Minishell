/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:56:10 by rabustam          #+#    #+#             */
/*   Updated: 2023/04/20 19:03:54 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_executor	init_executor(t_mini *ms)
{
	int			i;
	t_executor	ex;

	ex.pid = 0;
	ex.status = 0;
	ex.n_pros = 1;
	ex.temp = ms -> token;
	ex.cmd = token_to_mat(ex.temp);
	while (ex.temp)
	{
		if (ex.temp->type == PIPE)
			ex.n_pros++;
		ex.temp = ex.temp->next;
	}
	ex.fd = ft_calloc(ex.n_pros, sizeof(int *));
	i = -1;
	while (++i < (ex.n_pros - 1))
		ex.fd[i] = ft_calloc(2, sizeof(int));
	i = -1;
	while (++i < (ex.n_pros - 1))
		pipe(ex.fd[i]);
	ex.temp = ms -> token;
	return (ex);
}

static int	exec_on_parent(t_mini *ms, int n_pros, char **cmd, int **fd)
{
	if (n_pros > 1)
		return (-1);
	if (!ft_strncmp (*cmd, "echo", 4))
		return (-1);
	if (!ft_strncmp (*cmd, "pwd", 3))
		return (-1);
	if (!ft_strncmp (*cmd, "env", 3))
		return (-1);
	if (!ft_strncmp (*cmd, "exit", 5))
		fd = (int **) free_mat((char **) fd);
	if (!execbi(ms, cmd, &ms->envp, ms->prompt))
		return (-1);
	return (n_pros);
}

static void	exec_on_child(t_mini *ms, t_executor *ex, int i)
{
	ex->pid = malloc(sizeof(pid_t) * ex->n_pros);
	while (++i < ex->n_pros)
	{
		if (i)
			ex->cmd = token_to_mat(ex->temp);
		ex->pid[i] = fork();
		if (ex->pid[i] == 0)
			child(ms, ex->cmd, ex->fd, i);
		while (ex->temp && ex->temp->type != PIPE)
			ex->temp = ex->temp->next;
		if (ex->temp && ex->temp->type == PIPE)
			ex->temp = ex->temp->next;
		ex->cmd = free_mat(ex->cmd);
	}
}

void	executor(t_mini *ms)
{
	int			i;
	int			j;
	t_executor	ex;

	ex = init_executor(ms);
	i = exec_on_parent(ms, ex.n_pros, ex.cmd, ex.fd);
	if (i > 0)
		ex.cmd = free_mat(ex.cmd);
	exec_on_child(ms, &ex, i);
	close_fds(ex.fd);
	j = -1;
	while (ex.fd[++j])
		ex.fd[j] = (int *) free_ptr((char *) ex.fd[j]);
	ex.fd = (int **) free_mat((char **) ex.fd);
	j = -1;
	while (++j < ex.n_pros)
		waitpid(ex.pid[j], &ex.status, 0);
	if (WIFEXITED(ex.status) && i != ex.n_pros)
		ms->error = WEXITSTATUS(ex.status);
	free(ex.pid);
}

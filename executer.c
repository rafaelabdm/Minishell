/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:56:10 by rabustam          #+#    #+#             */
/*   Updated: 2022/12/20 20:13:59 by rabustam         ###   ########.fr       */
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
	ret = malloc(sizeof(char *) * (i + 1));
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

void	run_scmd(char **cmd, char **envp)
{
	char	*path;

	if (ft_strchr(cmd[0], '/'))
		path = ft_strdup(cmd[0]);
	else
		path = ft_strjoin("/usr/bin/", cmd[0]);
	execve(path, cmd, envp);
	perror(ft_strjoin("Minishell: ", cmd[0]));
	free_list(cmd);
	free(path);
}

int	is_redin(char **cmd, int i)
{
	int	file;

	file = -1;
	if (!ft_strncmp(cmd[i], "<", 2))
		file = open(cmd[i + 1], O_RDONLY);
	else if (!ft_strncmp(cmd[i], "<<", 3))
		file = 0; //HEREDOC :)
	return (file);
}

int	is_redout(char **cmd, int i)
{
	int	file;

	file = -1;
	if (!ft_strncmp(cmd[i], ">", 2))
		file = open(cmd[i + 1], O_WRONLY | O_CREAT, 0777);
	else if (!ft_strncmp(cmd[i], ">>", 3))
		file = open(cmd[i + 1], O_APPEND | O_WRONLY | O_CREAT, 0777);
	return (file);
}

int	is_redirect(char *cmd)
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

char **redirect(char **cmd)
{
	int		fd[2];
	char 	**ret;
	int		i, j;
	
	fd[0] = -1;
	fd[1] = -1;
	i = 0;
	while (cmd[i])
		i++;
	ret = ft_calloc(i + 1, sizeof(char *));
	
	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (is_redirect(cmd[i]))
		{
			fd[0] = is_redin(cmd, i);
			fd[1] = is_redout(cmd, i);
			i = i + 2;
		}
		else
			ret[j++] = ft_strdup(cmd[i++]);
	}
	if (fd[0] != -1)
	{
		dup2(fd[0], 0);
		close(fd[0]);
	}
	if (fd[1] != -1)
	{
		dup2(fd[1], 1);
		close(fd[1]);
	}
	return ret;
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

void	first_child(int **fd, char **cmd, char **envp)
{
	if (*fd)
		dup2(fd[0][1], 1);
	close_fds(fd);
	cmd = redirect(cmd);
	//if build-in -> execbi ... else ... 
	run_scmd(cmd, envp);
	exit(errno);
}

void	last_child(int **fd, int i, char **cmd, char **envp)
{
	dup2(fd[i - 1][0], 0);
	close_fds(fd);
	cmd = redirect(cmd);
	//if build-in -> execbi ... else ... 
	run_scmd(cmd, envp);
	exit(errno);
}

void 	middle_child(int **fd, int i, char **cmd, char **envp)
{
	dup2(fd[i - 1][0], 0);
	dup2(fd[i][1], 1);
	close_fds(fd);
	cmd = redirect(cmd);
	//if build-in -> execbi ... else ... 
	run_scmd(cmd, envp);
	exit(errno);
}

void    pipex(t_token *head, char **envp)
{
	t_token *temp;
	char	**cmd;
	int   **fd;
	int   status = 0;
	pid_t pid;
	int i;
	int	n_pros = 1;

	temp = head;
	/*NUMERO DE PROCESSOS*/
	while (temp)
	{
		if (temp->type == PIPE)	
			n_pros++;
		temp = temp->next;
	}

	fd = ft_calloc(n_pros, sizeof(int *));
	fd[n_pros - 1] = NULL;

	i = -1;
	while (++i < (n_pros - 1))
		fd[i] = ft_calloc(2, sizeof(int));
	
	i = -1;
	while (++i < (n_pros - 1))
		pipe(fd[i]);


	temp = head;
	i = 0;
	while (i < n_pros)
	{
		cmd = token_to_mat(temp);
		pid = fork();
		if (pid == 0)
		{
			if (i == 0)
				first_child(fd, cmd, envp);
			else if (i + 1 == n_pros)
				last_child(fd, i, cmd, envp);
			else
				middle_child(fd, i, cmd, envp);
		}
		while (temp && temp->type != PIPE)
			temp = temp->next;
		if (temp && temp->type == PIPE)
			temp = temp->next;
		free_list(cmd);
		i++;
	}

	close_fds(fd);
	i = -1;
	while (fd[++i])
		free(fd[i]);
	free(fd);
	waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        status = WEXITSTATUS(status);       
	printf("exit status: %d\n", status); // status aqui é mini.error
}

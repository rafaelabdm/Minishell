#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "./libft/libft.h"

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


// int	is_redin(t_token *token)
// {
// 	int	file;

// 	file = -1;
// 	if (!ft_strncmp(token->cmd, "<", 2))
// 		file = open(token->next>cmd, O_RDONLY);
// 	else if (!ft_strncmp(token->cmd, "<<", 3))
// 		file = 0;
// 	return (file);
// }

// int	is_redout(t_token *token)
// {
// 	int	file;

// 	file = -1;
// 	if (!ft_strncmp(token->cmd, ">", 2))
// 		file = open(token->next>cmd, O_WRONLY | O_CREAT);
// 	else if (!ft_strncmp(token->cmd, ">>", 3))
// 		file = open(token->next>cmd, O_APPEND | O_CREAT);
// 	return (file);
// }

// int	*redirect(t_token **head)
// {
// 	t_token	*token;
// 	int		fd[2];

// 	token = *head;
// 	fd[0] = -1;
// 	fd[1] = -1;
// 	while (token && token->type != PIPE)
// 	{
// 		if (token->type == REDIRECT)
// 		{
// 			fd[0] = is_redin(token);
// 			fd[1] = is_redout(token);
// 			if (fd[0] >= 0 || fd[1] > 0)
// 				remove_tokens(token);
// 		}	
// 	}
// 	if (fd[0] >= 0)
// 		dup2(fd[0], 0);
// 	if (fd[1] > 0)
// 		dup2(fd[1], 1);
// 	return (fd);
// }

void	first_child(int **fd, char **cmd, char **envp)
{
	// printf("COMEÇO: %s\n", cmd[0]);
	//if (redirect())
	dup2(fd[0][1], 1);
	close_fds(fd);
	//if build-in -> execbi ... else ... 
	execve(ft_strjoin("/usr/bin/", cmd[0]), cmd, envp);
	perror(ft_strjoin("minishell: ", cmd[0]));
	exit(1);
}

void	last_child(int **fd, int i, char **cmd, char **envp)
{
	// printf("FIM: %s\n", cmd[0]);
	//if (!redirect())
	dup2(fd[i - 1][0], 0);
	close_fds(fd);
	//if build-in -> execbi ... else ... 
	execve(ft_strjoin("/usr/bin/", cmd[0]), cmd, envp);
	perror(ft_strjoin("minishell: ", cmd[0]));
	exit(2);
}

void 	middle_child(int **fd, int i, char **cmd, char **envp)
{
	// printf("MEIO: %s\n", cmd[0]);
	//if (!redirect())
	dup2(fd[i - 1][0], 0);
	dup2(fd[i][1], 1);
	close_fds(fd);
	//if build-in -> execbi ... else ... 
	execve(ft_strjoin("/usr/bin/", cmd[0]), cmd, envp);
	perror(ft_strjoin("minishell: ", cmd[0]));
	exit(3);
}

void    pipex(char ***cmd, char **envp)
{
	int   **fd;
	int   status;
	pid_t pid;
	int i;
	int	n_pros = 0;

	/*NUMERO DE PROCESSOS*/
	while (cmd[n_pros])
		n_pros++;
	fd = ft_calloc(n_pros, sizeof(int *));
	fd[n_pros - 1] = NULL;

	i = -1;
	while (++i < (n_pros - 1))
		fd[i] = ft_calloc(2, sizeof(int));
	
	i = -1;
	while (++i < (n_pros - 1))
		pipe(fd[i]);

	i = 0;
	while (i < n_pros)
	{
		pid = fork();
		if (pid == 0)
		{
			if (i == 0)
				first_child(fd, cmd[i], envp);
			else if (i + 1 == n_pros)
				last_child(fd, i, cmd[i], envp);
			else
				middle_child(fd, i, cmd[i], envp);
		}
		i++;
	}

	close_fds(fd);
	i = -1;
	while (fd[++i])
		free(fd[i]);
	free(fd);
	waitpid(pid, &status, 0);
	printf("exit status: %d\n", status); // status aqui é mini.error
}

int main(int ac, char **ag, char **envp)
{
	char ***cmd;

	cmd = ft_calloc(5, sizeof(char **));

	cmd[0] = ft_split("ls -l", ' ');
	cmd[1] = ft_split("grep Dec", ' ');
	cmd[2] = ft_split("sort -r", ' ');
	cmd[3] = ft_split("wc -l", ' ');
	cmd[4] = NULL;

	pipex(cmd, envp);

	int i = -1;
	int j = -1;
 
	while (cmd[++i])
	{
		j = 0;
		while (cmd[i][j])
		{
			free(cmd[i][j]);
			j++;
		}
		free(cmd[i]);
	}
	free(cmd);
	
	return (0);
}

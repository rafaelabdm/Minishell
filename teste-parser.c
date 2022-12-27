/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste-parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:03:57 by rabustam          #+#    #+#             */
/*   Updated: 2022/12/27 15:41:09 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	free_list(char **list)
{
	int	i;

	i = -1;
	while (list[++i])
		free(list[i]);
	free(list);
}

int	is_buildin(char *token)
{
	char	**list;
	int		i;

	list = malloc(sizeof(char *) * 8);
	if (!list)
		return (-1);
	list[0] = ft_strdup("echo");
	list[1] = ft_strdup("cd");
	list[2] = ft_strdup("pwd");
	list[3] = ft_strdup("export");
	list[4] = ft_strdup("unset");
	list[5] = ft_strdup("env");
	list[6] = ft_strdup("exit");
	list[7] = NULL;
	i = -1;
	while (list[++i])
	{
		if (!ft_strncmp(token, list[i], ft_strlen(token)))
		{
			free_list(list);
			return (1);
		}
	}
	free_list(list);
	return (0);
}

void	insert_token(t_token **head, char *token)
{
	t_token	*new;
	t_token	*temp;

	new = malloc(sizeof(t_token));
	new->cmd = ft_strdup(token);
	new->type = 0;
	new->prev = NULL;
	new->next = NULL;
	if (!*head)
	{
		*head = new;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	new->prev = temp;
	temp->next = new;
}

//------------------------------------------------------------------
//LEXER
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

char	*filler(char *input, int pos)
{
	char	*ret;
	int		i;
	int		j;

	ret = malloc(ft_strlen(input) + 3);
	if (!ret)
		return (NULL);
	i = -1;
	j = -1;
	while (++j < pos)
		ret[j] = input[++i];
	i++;
	ret[j++] = SEP;
	ret[j++] = input[i++];
	if (input[i] == input[i - 1] && input[i] != '|') // mudei TRATEI O PIPE
		ret[j++] = input[i++];
	ret[j++] = SEP;
	while (input[i])
		ret[j++] = input[i++];
	ret[j] = '\0';
	free(input);
	return (ret);
}

char	**lexer(char *input)
{
	int		i;
	int		quotes;
	char	**ret;

	i = -1;
	quotes = 0;
	while (input[++i])
	{
		if ((input[i] == '|' || input[i] == '>' || input[i] == '<' ) && !quotes)
		{
			input = filler(input, i);
			i = i + 2;
		}	
		else if (input[i] == '\"' || input[i] == '\'')
			quotes = check_quotes(input[i], quotes);
	}
	if (quotes)
	{
		free(input);
		return (NULL);
	}
	ret = ft_split(input, SEP);
	free(input);
	return (ret);
}

//----------------------------------------------------------------------
//PARSER
void    *free_ptr(void *ptr)
{
	if (!ptr)
		return (NULL);
    free (ptr);
    ptr = NULL;
    return (ptr);
}

char	*fill_args(char *input, int pos)
{
	char	*ret;
	int		i;
	int		j;

	ret = malloc(ft_strlen(input) + 2);
	if (!ret)
		return (NULL);
	i = -1;
	j = -1;
	while (++j < pos)
		ret[j] = input[++i];
	i++;
	ret[j++] = SEP;
	while (input[i])
		ret[j++] = input[i++];
	ret[j] = '\0';
	return (ret);
}

char	**split_args(char *input)
{
	int		i;
	int		quotes;
	char	*temp;
	char	**ret;

	i = -1;
	quotes = 0;
	temp = NULL;
	while (input[++i])
	{
		if (input[i] == ' ' && !quotes)
			input[i] = SEP;
		// else if ((input[i] == '\"' || input[i] == '\'') && !quotes)
		// {
		// 	quotes = check_quotes(input[i], quotes);
		// 	input = fill_args(input, i++);
		// 	temp = free_ptr(temp);
		// 	temp = input;
		// }		
		else if (input[i] == '\"' || input[i] == '\'')
			quotes = check_quotes(input[i], quotes);
	}
	ret = ft_split(input, SEP);
	temp = free_ptr(temp);
	return (ret);
}

void	define_type(t_token **head)
{
	t_token	*token;
	int		exec;

	exec = 0;
	token = *head;
	while (token)
	{
		if (!ft_strncmp(token->cmd, "|", ft_strlen(token->cmd)))
		{
			token->type = PIPE;
			exec = 0;
		}
		else if (!ft_strncmp(token->cmd, ">>", ft_strlen(token->cmd)) || \
		!ft_strncmp(token->cmd, "<", ft_strlen(token->cmd)))
			token->type = REDIRECT;
		else if (!ft_strncmp(token->cmd, "<<", ft_strlen("<<")))
			token->type = HEREDOC;
		else if (is_buildin(token->cmd) && !exec)
		{
			token->type = BUILDIN;
			exec = 1;
		}
		else if (token->prev && token->prev->type == REDIRECT)
			token->type = FILE;
		else if (!token->prev || !exec)
		{
			token->type = EXECVE;
			exec = 1;
		}
		else
			token->type = ARG;
		token = token->next;
	}
}

void	parser(t_token **head, char *str)
{
	char	**cmdlist;
	char	**cmd;
	int		i;
	int		j;

	cmdlist = lexer(str);
	if (!cmdlist)
	{
		//exit_handler() -> substituir
		printf("Error: unclosed quotes\n");
		return ;
	}
	i = -1;
	while (cmdlist[++i])
	{
		j = -1;
		cmd = split_args(cmdlist[i]);
		while (cmd[++j])
			insert_token(head, cmd[j]);
		free_list(cmd);
	}
	//acrescentado
	if (!ft_strncmp(cmdlist[--i], "|", 2))
		parser(head, readline("> "));
	free_list(cmdlist);
	define_type(head);
}

//-------------------------------------------------------------------
//EXPANDER
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
		free(temp);
	}
	free_list(mat);
	return (str);
}

int	count_expansions(char *cmd)
{
	int	i;

	i = 0;
	while (*cmd)
	{
		if (*cmd == '$')
			i++;
		cmd++;
	}
	return (i);
}

char	*exit_status(char *f, char *cmd)
{
	char	*ret;

	ret = NULL;
	if (!*cmd)
	{
		free(f);
		return (ft_strdup("$"));
	}
	if (cmd + 1)
		ret = ft_strdup(++cmd);
	free(f);
	//ESSA STRJOIN DA FREE NA CHAR *S2!!!!!
	return (ft_strjoin_gnl("EXIT STATUS", ret));	
}

char	*get_envp(char *cmd, char **envp)
{
	char	*ret;
	int		len;

	ret = cmd;
	cmd++;
	if (*cmd == '{')
	{
		cmd++;
		len = ft_strlen(cmd) - 1;
	}
	else
		len = ft_strlen(cmd);
	if (*cmd == '?' || len == 0) //acrescentado
		return exit_status(ret, cmd);
	while (*envp)
	{
		if (!ft_strncmp(cmd, *envp, len))
		{
			free(ret);
			return (ft_strdup(*envp + len + 1));
		}
		envp++;
	}
	free(ret);
	return (ft_strdup(""));
}

char	*expand(char *cmd, char **envp)
{
	char	**hold_str;
	int		ex;
	int		start;
	int		end;
	int		quotes;

	ex = (count_expansions(cmd) * 2) + 2;
	hold_str = malloc(sizeof(char *) * ex);
	if (!hold_str)
		return (NULL);
	hold_str[ex - 1] = NULL;
	ex = 0;
	start = 0;
	end = -1;
	quotes = 0;
	while (cmd[++end])
	{
		quotes = check_quotes(cmd[end], quotes);
		if (cmd[end] == '$' && quotes != 2)
		{
			hold_str[ex++] = ft_substr(cmd, start, end - start);
			start = end;
		}
		else if (cmd[start] == '$' && cmd[end] != '{' && cmd[end] != '?' \
		&& !ft_isalnum(cmd[end])) //mudei acrescentei '?' e tirei quotes
		{
			hold_str[ex++] = get_envp(ft_substr(cmd, start, end - start), envp);
			if (cmd[end] == '}' && cmd[start + 1] == '{') //mudei acrescentei segunda verificação
				end++;
			start = end;
		}
	}
	if (cmd[start] == '$')
		hold_str[ex++] = get_envp(ft_substr(cmd, start, end - start), envp);
	else
		hold_str[ex++] = ft_substr(cmd, start, end - start);
	hold_str[ex] = NULL;
	return (ft_mattstr_copy(hold_str));
}

char	*expand_quotes(char *cmd)
{
	int	i;
	int	quotes;
	char	**ret;
	
	i = -1;
	quotes = 0;
	while (cmd[++i])
	{
		quotes = check_quotes(cmd[i], quotes);
		if ((cmd[i] == '\'' || cmd[i] == '\"') && !quotes)
			cmd[i] = SEP;
		else if ((cmd[i] == '\'' && quotes == 2) ||\
		(cmd[i] == '\"' && quotes == 1))
			cmd[i] = SEP;
	}
	ret = ft_split(cmd, SEP);
	if (!*ret)
	{
		free_list(ret);
		return (ft_strdup(""));
	}
	return (ft_mattstr_copy(ret));
}

void	expander(t_token **head, char **envp)
{
	char	*temp;
	t_token	*token;

	token = *head;
	while (token)
	{
		if (ft_strchr(token->cmd, '$'))
		{
			temp = token->cmd;
			token->cmd = expand(token->cmd, envp);
			if (token->cmd == NULL)
				token->cmd = temp;
			else
				free(temp);
		}
		temp = token->cmd;
		token->cmd = expand_quotes(token->cmd);
		free(temp);
		token = token->next;
	}
}
//-------------------------------------------------------------------
//EXECUTER

char	**token_to_mat(t_token *token) //token to matrix
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
	//se der erro na exec essas linhas abaixo serão executadas
	//printf("Minishell: %s: %s\n", cmd[0], strerror(errno)); //copiei do bash :)
	perror(ft_strjoin("Minishell: ", cmd[0]));
	free_list(cmd);
	free(path);
}

//------------------------------------------------------------------
//TESTE

// < teste  TESTE < teste2 grep rafa > teste
// TESTE grep rafa
int	heredoc(const char *eof, char **envp)
{
	char	*input;
	int		file;

	input = NULL;
	file = open("__heredoc", O_WRONLY|O_CREAT|O_EXCL|O_TRUNC, 0600);
	while (1)
	{
		input = readline("> ");
		if (!ft_strncmp(eof, input, ft_strlen(input)))
		{
			free(input);
			break ;
		}
		if (*eof != '\'' && *eof != '\"' && ft_strchr(input, '$'))
			input = expand(input, envp);
		write(file, input, ft_strlen(input));
		write(file, "\n", 1);
		free(input);
		input = NULL;
	}
	close(file);
	file = open("__heredoc", O_RDONLY);
	unlink("__heredoc");
	return (file);
}

int	is_redin(char **cmd, int i, char **envp)
{
	static int	file = -1;

	if (!ft_strncmp(cmd[i], "<", 2))
		file = open(cmd[i + 1], O_RDONLY);
	else if (!ft_strncmp(cmd[i], "<<", 3))
		file = heredoc(cmd[i + 1], envp);
	return (file);
}

int	is_redout(char **cmd, int i)
{
	static int	file = -1;

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

char **redirect(char **cmd, char **envp, int *out, int *in)
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
			fd[0] = is_redin(cmd, i, envp);
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
	int	out;
	int	in;
	
	out = 0;
	in = 0;
	cmd = redirect(cmd, envp, &out, &in);
	if (*cmd == NULL) //caso o comando sea apenas redirecionamento (heredoc)
		exit(0);
	if (*fd && !out)
		dup2(fd[0][1], 1);
	close_fds(fd);
	//if build-in -> execbi ... else ... 
	run_scmd(cmd, envp);
	exit(errno);
}

void	last_child(int **fd, int i, char **cmd, char **envp)
{
	int out;
	int	in;
	
	out = 0;
	in = 0;
	cmd = redirect(cmd, envp, &out, &in);
	if (!in)
		dup2(fd[i - 1][0], 0);
	close_fds(fd);
	//if build-in -> execbi ... else ... 
	run_scmd(cmd, envp);
	exit(errno);
}

void 	middle_child(int **fd, int i, char **cmd, char **envp)
{
	int	out;
	int	in;
	
	out = 0;
	in = 0;
	cmd = redirect(cmd, envp, &out, &in);
	if (!in)
		dup2(fd[i - 1][0], 0);
	if (!out)
		dup2(fd[i][1], 1);
	close_fds(fd);
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
	//printf("exit status: %d\n", status); // status aqui é mini.error
}
//-------------------------------------------------------------------
// SYNTAX ERRORS

int	syntax_checker(t_token *token)
{
	t_token *temp;

	temp = token;
	while (temp)
	{
		if (temp->type == PIPE)
		{
			if (temp->next && temp->next->type == PIPE)
				printf("minishell: syntax error near unexpected token `%s'\n", temp->next->cmd);
				return (2);
		}
		if (temp->type == REDIRECT)
		{
			if (temp->next && (temp->next->type == PIPE || \
			temp->next->type == REDIRECT || temp->next->type == HEREDOC))
				printf("minishell: syntax error near unexpected token `%s'\n", temp->next->cmd);
				return (2);
		}
		temp = temp->next;
	}
	return (0);
}

//-------------------------------------------------------------------
int	main(int argc, char **argv, char **envp)
{
	//char *str = ft_strdup("ls -l| sort -r | grep Dec| wc -l");
	//char *str = ft_strdup("ls -l | grep Dec >> teste ");
	//char *str = ft_strdup("echo \"'rafaela $SOBRENOME de miranda'\"'${PWD}'");
	// char *str = ft_strdup("echo $USER '\"$USER\"'");
	char *str = ft_strdup("clear");
	//char *str = ft_strdup("/usr/bin/ls -la ");
	//char *str = ft_strdup("ec\"ho\" $PWD");
	//char *str = ft_strdup("echo \"'$MINI\"");
	//char *str = ft_strdup("echo $PWD###");
	//char *str = ft_strdup("ls -l > teste | wc");
	//char *str = ft_strdup("ls | cat > teste");

	t_token *cmdlist;

	cmdlist = NULL;
	parser(&cmdlist, str);
	syntax_checker(cmdlist);

	//EXPANDER
	(void)argc;
	(void)argv;
	expander(&cmdlist, envp);

	//EXECUTOR
	pipex(cmdlist, envp);

	
	//para visualizar:
	t_token *temp;
	// temp = cmdlist;
	// int 	p = 1; //processos necessários
	// while (temp)
	// {
	// 	printf("cmd: %s - type: %d\n", temp->cmd, temp->type);
	// 	if (temp->type == PIPE)
	// 		p++;
	// 	temp = temp->next;
	// }
	// printf("We have %d processes!\n\n", p);

	
	//free
	t_token *f;
	temp = cmdlist;
	while (temp)
	{
		f = temp;
		temp = temp->next;
		free(f->cmd);
		free(f);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:03:57 by rabustam          #+#    #+#             */
/*   Updated: 2022/11/26 15:40:59 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	insert_token(t_token **head, char *token)
{
	t_token	*new;
	t_token	*temp;

	new = ft_calloc(1, sizeof(t_token));
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

static int	is_buildin(char *token)
{
	char	**list;
	int		i;

	list = ft_calloc(8, sizeof(char *));
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
			list = free_mat(list);
			return (1);
		}
	}
	list = free_mat(list);
	return (0);
}

static char	**split_args(char *input)
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
		else if (input[i] == '\"' || input[i] == '\'')
			quotes = check_quotes(input[i], quotes);
	}
	ret = ft_split(input, SEP);
	temp = free_ptr(temp);
	return (ret);
}

static void	define_type(t_token **head)
{
	t_token	*token;

	token = *head;
	while (token)
	{
		if (!ft_strncmp(token->cmd, "|", ft_strlen(token->cmd)))
			token->type = PIPE;
		else if (!ft_strncmp(token->cmd, ">>", ft_strlen(token->cmd)) || \
		!ft_strncmp(token->cmd, "<", ft_strlen(token->cmd)))
			token->type = REDIRECT;
		else if (!ft_strncmp(token->cmd, "<<", ft_strlen("<<")))
			token->type = HEREDOC;
		else if (is_buildin(token->cmd))
			token->type = BUILDIN;
		else if (!token->prev || token->prev->type == PIPE)
			token->type = EXECVE;
		else if (token->prev->type == REDIRECT)
			token->type = ARG_FILE;
		else
			token->type = ARG;
		token = token->next;
	}
}

int	parser(t_token **head, char *str)
{
	char	**cmdlist;
	char	**cmd;
	int		i;
	int		j;

	cmdlist = lexer(str);
	if (!cmdlist)
	{
		ft_putstr_fd("-minishell: parser: unclosed quotes\n", 2);
		cmdlist = free_mat(cmdlist);
		return (1);
	}
	i = -1;
	while (cmdlist[++i])
	{
		j = -1;
		cmd = split_args(cmdlist[i]);
		while (cmd[++j])
			insert_token(head, cmd[j]);
		cmd = free_mat(cmd);
	}
	check_pipe (cmdlist[--i], head);
	cmdlist = free_mat(cmdlist);
	define_type(head);
	return (0);
}

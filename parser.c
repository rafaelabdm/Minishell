/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:03:57 by rabustam          #+#    #+#             */
/*   Updated: 2022/11/19 18:16:40 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	**split_args(char *input)
{
	int		i;
	int		quotes;

	i = -1;
	quotes = 0;
	while (input[++i])
	{
		if (input[i] == ' ' && !quotes)
			input[i] = SEP;
		else if (input[i] == '\"' || input[i] == '\'')
			quotes = check_quotes(input[i], quotes);
	}
	return (ft_split(input, SEP));
}

void	define_type(t_token **head)
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
			token->type = FILE;
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
	i = -1;
	while (cmdlist[++i])
	{
		j = -1;
		cmd = split_args(cmdlist[i]);
		while (cmd[++j])
			insert_token(head, cmd[j]);
		free_list(cmd);
	}
	free_list(cmdlist);
	define_type(head);
}

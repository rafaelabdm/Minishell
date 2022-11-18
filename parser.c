/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:03:57 by rabustam          #+#    #+#             */
/*   Updated: 2022/11/18 22:08:13 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./minishell.h"

void	free_list(char **list)
{
	int i;

	i = -1;
	while (list[++i])
		free(list[i]);
	free(list);
}

int	is_buildin(char *token)
{
	char **list;
	int i;

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
		if(!ft_strncmp(token, list[i], ft_strlen(token)))
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
	t_token *temp;
	
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

//-------------------------------------------------------------------------------
//LEXER

int		check_quotes(char c, int quotes)
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
	char *ret;
	int i;
	int j;

	ret = malloc(ft_strlen(input) + 3);
	if (!ret)
	 	return (NULL);
	i = -1;
	j = -1;
	while (++j < pos)
		ret[j] = input[++i];
	i++;
	ret[j++] = 96;
	ret[j++] = input[i++];
	ret[j++] = 96;
	while (input[i])
	{
		ret[j] = input[i];
		j++;
		i++;
	}
	ret[j] = '\0';
	free(input);
	return (ret);
}

char	**lexer(char *input)
{
	int i;
	int quotes;
	char **ret;

	i = -1;
	quotes = 0;
	while (input[++i])
	{
		if ((input[i] == '|' || input[i] == '>' || input[i] == '<' ) && !quotes)
		{
			input = filler(input, i);
			i++;
		}	
		else if (input[i] == '\"' || input[i] == '\'')
			quotes = check_quotes(input[i], quotes);
	}
	ret = ft_split(input, 96);
	free(input);
	return (ret);
}

//----------------------------------------------------------------------
//PARSER

char	**split_args(char *input)
{
	int		i;
	int		quotes;

	i = -1;
	quotes = 0;
	while (input[++i])
	{
		if (input[i] == ' ' && !quotes)
			input[i] = 96;
		else if (input[i] == '\"' || input[i] == '\'')
			quotes = check_quotes(input[i], quotes);
	}
	return (ft_split(input, 96));
}

void	parser(t_token **head, char *str)
{
	char	**cmdlist;
	char	**cmd;
	int		i;
	int 	j;

	cmdlist = lexer(str);
	i = -1;
	while (cmdlist[++i])
	{
		j = -1;
		cmd = split_args(cmdlist[i]);
		while (cmd[++j])
			insert_token(head, cmd[j]);
	}
	free_list(cmdlist);
	free_list(cmd);
}

//-------------------------------------------------------------------------
void	define_type(t_token **head)
{
	t_token *token;
	token = *head;

	while (token)
	{
		if (!ft_strncmp(token->cmd, "|", ft_strlen(token->cmd)))
			token->type = PIPE;
		else if (!ft_strncmp(token->cmd, ">>", ft_strlen(token->cmd)) ||\
		!ft_strncmp(token->cmd, "<", ft_strlen(token->cmd)))
			token->type = REDIRECT;
		else if(!ft_strncmp(token->cmd, "<<", ft_strlen("<<")))
			token->type = HEREDOC; //invés de ler um arquivo lê do terminal
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
//-------------------------------------------------------------------
int main(int argc, char **argv, char **envp)
{
	char *str = ft_strdup("cat pipes.c| echo \"rafa | show\" >file |wc -l");
	//char *str = ft_strdup("ls <teste -la");
	t_token *cmdlist;

	cmdlist = NULL;
	parser(&cmdlist, str);
	define_type(&cmdlist);


	//para visualizar:
	t_token *temp;
	temp = cmdlist;
	int 	p = 1; //processos necessários
	while (temp)
	{
		printf("cmd: %s - type: %d\n", temp->cmd, temp->type);
		if (temp->type == PIPE)
			p++;
		temp = temp->next;
	}
	printf("We have %d processes!\n", p);

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


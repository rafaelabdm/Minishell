/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:03:57 by rabustam          #+#    #+#             */
/*   Updated: 2022/11/18 15:44:39 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./minishell.h"

//PARSER: quebra os comandos em palavras

//PIPE 10
//SIMPLE_CMD 11
//BUILDIN 12
//ARG 13
//FILE 14
//REDIRECT 15

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
			return (1);
	}
	return (0);
}

int	define_type(char *token)
{
	static int prev = 0;

	if (!ft_strncmp(token, "|", ft_strlen(token)))
		prev = PIPE;
	else if (is_buildin(token))
		prev = BUILDIN;
	else if (!prev || prev == PIPE)
		prev = EXECVE;
	else
		prev = ARG;
	return (prev);
}

void	insert_token(t_token **head, char *token)
{
	t_token	*new;
	t_token *temp;
	
	new = malloc(sizeof(t_token));
	new->cmd = ft_strdup(token);
	new->type = define_type(token);
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

char	**lexer(char *input, int sep)
{
	int i;
	int quotes;

	i = -1;
	quotes = 0;
	while (input[++i])
	{
		if ((input[i] == sep) && !quotes)
			input[i] = 96;

		else if (input[i] == '\"' || input[i] == '\'')
			quotes = check_quotes(input[i], quotes);
	}
	return (ft_split(input, 96));
}

void	parser(t_token **head, char *str)
{
	char	**cmdlist;
	int		i;

	cmdlist = lexer(str, '|');
	i = -1;
	while (cmdlist[++i])
	{
		printf("%s\n", cmdlist[i]);
		//insert_token(head, cmdlist[i]);
	}
}

int main(int argc, char **argv, char **envp)
{
	char *str = ft_strdup("cat pipes.c | echo \"rafa | show\" >> file");
	t_token *cmdlist;

	cmdlist = NULL;
	parser(&cmdlist, str);
	
	/* //para visualizar:
	t_token *temp;
	int 	p = 0; //processos necessários
	temp = cmdlist;
	while (temp)
	{
		printf("cmd: %s, type: %d\n", temp->cmd, temp->type);
		p++;
		temp = temp->next;
	}
	printf("We have %d processes!\n", p); */

	return (0);
}


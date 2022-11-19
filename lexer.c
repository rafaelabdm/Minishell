/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 21:06:45 by rabustam          #+#    #+#             */
/*   Updated: 2022/11/18 18:42:37 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "./minishell"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "./libft/libft.h"

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

int main(void)
{
	char *input = ft_strdup("rafaela|miranda>>\"busta|mante\"");
	char **cmdlist;
	int i = -1;
	
	cmdlist = lexer(input);
	while(cmdlist[++i])
		printf("%s\n", cmdlist[i]);
}

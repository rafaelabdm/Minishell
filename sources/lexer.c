/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 21:06:45 by rabustam          #+#    #+#             */
/*   Updated: 2022/11/25 13:56:54 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*filler(char *input, int pos)
{
	char	*ret;
	int		i;
	int		j;

	ret = ft_calloc(ft_strlen(input) + 3, sizeof (char));
	if (!ret)
		return (NULL);
	i = -1;
	j = -1;
	while (++j < pos)
		ret[j] = input[++i];
	i++;
	ret[j++] = SEP;
	ret[j++] = input[i++];
	if (input[i] == input[i - 1] && input[i] != '|')
		ret[j++] = input[i++];
	ret[j++] = SEP;
	while (input[i])
		ret[j++] = input[i++];
	ret[j] = '\0';
	input = free_ptr(input);
	return (ret);
}

char	**lexer(char *input)
{
	int		i;
	int		quotes;
	char	*temp;
	char	**ret;

	i = -1;
	quotes = 0;
	temp = ft_strdup(input);
	while (temp && temp[++i])
	{
		if ((temp[i] == '|' || temp[i] == '>' || temp[i] == '<' ) && !quotes)
		{
			temp = filler(temp, i);
			i = i + 2;
		}	
		else if (temp[i] == '\"' || temp[i] == '\'')
			quotes = check_quotes(temp[i], quotes);
	}
	if (quotes)
		temp = free_ptr(temp);
	ret = ft_split(temp, SEP);
	temp = free_ptr(temp);
	return (ret);
}

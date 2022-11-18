/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 21:06:45 by rabustam          #+#    #+#             */
/*   Updated: 2022/11/17 21:07:13 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell"

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

char	**lexer(char *input)
{
	int i;
	int quotes;

	i = -1;
	quotes = 0;
	while (input[++i])
	{
		if ((input[i] == '|') && !quotes)
			input[i] = 96;

		else if (input[i] == '\"' || input[i] == '\'')
			quotes = check_quotes(input[i], quotes);
	}
	return (ft_split(input, 96));
}

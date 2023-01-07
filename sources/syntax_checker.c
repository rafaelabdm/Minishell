/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 09:14:32 by rabustam          #+#    #+#             */
/*   Updated: 2022/12/28 09:14:32 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_next(t_mini *ms, t_token *token, int type)
{
	if (type == PIPE && token->next && token->next->type == PIPE)
	{
		ft_printf("minishell: syntax error near unexpected token `%s'\n", \
		token->next->cmd);
		ms->error = 2;
		return (2);
	}
	else if ((type == REDIRECT && token->next == NULL) || \
	(type == REDIRECT && (token->next->type == PIPE || \
	token->next->type == REDIRECT || token->next->type == HEREDOC)))
	{
		ft_printf("minishell: syntax error near unexpected token `%s'\n", \
		token->cmd);
		ms->error = 2;
		return (2);
	}
	return (0);
}

int	syntax_checker(t_mini *ms)
{
	t_token	*temp;

	temp = ms->token;
	while (temp)
	{
		if (temp->type == PIPE)
		{
			if (check_next(ms, temp, PIPE))
				return (2);
		}
		else if (temp->type == REDIRECT)
		{
			if (check_next(ms, temp, REDIRECT))
				return (2);
		}
		else if (ft_strchr(temp->cmd, '\\'))
		{
			ft_printf("minishell: syntax error, token `\\' is not accepted\n");
			ms->error = 2;
			return (2);
		}
		temp = temp->next;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 10:23:49 by rabustam          #+#    #+#             */
/*   Updated: 2022/12/29 10:23:49 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_pipe(char *cmd, t_token **head)
{
	char	*input;

	input = NULL;
	if (!ft_strncmp(cmd, "|", 2))
	{
		input = readline("> ");
		parser(head, input);
		input = free_ptr(input);
	}
}

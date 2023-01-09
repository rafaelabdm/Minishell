/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 14:00:23 by rapdos-s          #+#    #+#             */
/*   Updated: 2023/01/04 14:00:23 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_mini *ms, char **cmd, char ***envp)
{
	size_t	i;

	if (cmd[1])
	{
		ft_putstr_fd ("-" PROMPT_MSG ": env: " INVALID_USAGE "\n", 2);
		ms -> error = 42;
	}
	else
	{
		i = 0;
		while (envp && *envp && envp[0][i])
		{
			ft_printf ("%s\n", envp[0][i]);
			i++;
		}
		ms -> error = 0;
	}
}

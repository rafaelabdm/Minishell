/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:35:25 by rapdos-s          #+#    #+#             */
/*   Updated: 2022/11/29 12:35:25 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_easter_egg(char **prompt, int set)
{
	if (set)
	{
		*prompt = free_ptr (*prompt);
		ft_printf ("\033[1;32mHi, I'm Frank :)\033[0m\n");
		*prompt = ft_strdup ("\033[1;32mfrank \033[0m> ");
	}
	else
	{
		*prompt = free_ptr (*prompt);
		ft_printf ("\033[1;32mBye, my friend o/\033[0m\n");
		*prompt = ft_strdup ("minishell > ");
	}
}

int	execbi(t_mini *ms, char **cmd, char ***envp, char *prompt)
{
	if (!cmd || !*cmd || !*envp || !prompt)
		return (-1);
	if (!ft_strncmp (*cmd, "echo", 5))
		ft_echo (ms, cmd);
	else if (!ft_strncmp (*cmd, "cd", 3))
		ft_cd (ms, cmd, envp);
	else if (!ft_strncmp (*cmd, "pwd", 4))
		ft_pwd (ms, cmd, *envp);
	else if (!ft_strncmp (*cmd, "export", 7))
		ft_export (ms, cmd, envp);
	else if (!ft_strncmp (*cmd, "unset", 6))
		ft_unset (ms, cmd, envp);
	else if (!ft_strncmp (*cmd, "env", 4))
		ft_env (ms, cmd, envp);
	else if (!ft_strncmp (*cmd, "hi_frank", 9))
		ft_easter_egg (&prompt, 1);
	else if (!ft_strncmp (*cmd, "bye_frank", 10))
		ft_easter_egg (&prompt, 0);
	else if (!ft_strncmp (*cmd, "exit", 5))
		ft_exit (ms, cmd);
	else
		return (0);
	return (1);
}

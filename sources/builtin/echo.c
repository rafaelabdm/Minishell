/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 08:25:38 by rapdos-s          #+#    #+#             */
/*   Updated: 2023/01/04 08:25:38 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_mini *ms, char **cmd)
{
	char	new_line;
	int		i;
	int		j;

	new_line = 1;
	i = 1;
	while (cmd && cmd[i] && !ft_strncmp (cmd[i], "-n", 2))
	{
		j = 2;
		while (cmd[i][j] == 'n')
			j++;
		if (cmd[i][j] != '\0')
			break ;
		new_line = 0;
		i++;
	}
	while (cmd && cmd[i])
	{
		ft_printf ("%s", cmd[i]);
		if (cmd[++i])
			ft_putchar_fd (' ', 1);
	}
	if (new_line)
		ft_printf ("\n");
	ms -> error = 0;
}

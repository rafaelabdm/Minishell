/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:28:03 by rabustam          #+#    #+#             */
/*   Updated: 2022/12/21 15:46:05 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//cat << EOF > teste

int	heredoc(const char *eof, char **envp)
{
	char	*input;
	int		file;

	input = NULL;
	file = open("heredoc", O_RDWR | O_CREAT, 0777);
	while (ft_strncmp(eof, input, ft_strlen(input)))
	{
		input = readline("> ");
		if (*eof != '\'' && *eof != '\"')
			input = expand(eof, envp);
		write(file, input, ft_strlen(input));
	}
	return (file);
}
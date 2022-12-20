/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:51:48 by rabustam          #+#    #+#             */
/*   Updated: 2022/12/20 14:23:05 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MINISHELL_H_
# define _MINISHELL_H_

# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h> //use -lreadline flag to compile
# include "libft/libft.h"

# define PIPE 10
# define EXECVE 11
# define BUILDIN 12
# define ARG 13
# define FILE 14
# define REDIRECT 15
# define HEREDOC 16

# define SEP 96

typedef struct s_token
{
	char			*cmd;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_cmd
{
	char			**cmd;
	int				**pipe;
	int				fd_in;
	int				fd_out;
	int				status;
	struct s_cmd	*next;
}	t_cmd;


#endif
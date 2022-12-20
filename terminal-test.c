/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal-test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:55:04 by rabustam          #+#    #+#             */
/*   Updated: 2022/12/15 14:05:49 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

// void	init_buildins_list(t_mini *mini)
// {
// 	mini->list = malloc(sizeof(char *) * 8); //number of buildins + 1
// 	if (!mini->list)
// 		printf("Deu ruim.\n");
// 	mini->list[0] = ft_strdup("echo");
// 	mini->list[1] = ft_strdup("cd");
// 	mini->list[2] = ft_strdup("pwd");
// 	mini->list[3] = ft_strdup("export");
// 	mini->list[4] = ft_strdup("unset");
// 	mini->list[5] = ft_strdup("env");
// 	mini->list[6] = ft_strdup("exit");
// 	mini->list[7] = NULL;
// }

void	echo(const char *str)
{
	printf("%s\n", str + 5);
}

void	parser(char *str)
{
	//split
	//operadores indicam numero de processos ( | && || )
	//ou redirecionamentos (>> << > <) -> dup2, dup
	//comandos chamam execve ou bild-in functions
	//argumentos implementam comandos até um operador

	char **cmdlist;
	int i;
	int is_cmd;
	
	cmdlist = ft_split(str, ' ');
	i = -1;
	is_cmd = 0;
	while (cmdlist[++i])
	{
		if (is_cmd == 0)
		{
			printf("cmd: %s\n", cmdlist[i]);
			is_cmd = 1;
		}
		else if (ft_strncmp(cmdlist[i], "|", ft_strlen(cmdlist[i])))
		{
			if (cmdlist[i][0] == '-')
				printf("flags: %s\n", cmdlist[i]);
			else
				printf("args: %s\n", cmdlist[i]);
		}
		else
		{
			printf("operator: %s\n", cmdlist[i]);
			is_cmd = 0;	
		}
	}
}

int main(int argc, char *argv[])
{
	char *cmdline;
	//t_mini mini;

	//init_buildins_list(&mini);

	if (argc != 1)
	{
		ft_putstr_fd("Usage: ./minishell\n", 2);
		return (1);
	}
	while (1)
	{
		cmdline = readline("Minishell > ");
		if (cmdline && cmdline[0] != '\0')
			add_history(cmdline); //see memory info
		if (*cmdline != '\0' && !ft_strncmp(cmdline, "exit", ft_strlen(cmdline)))
		{
			free(cmdline);
			printf("Bye!\n");
			return (0);
		}
		parser(cmdline);
		//is_buildin(cmdline);
	}
	return (0);
}


// int	main(void)
// {
// 	t_mini mini;

// 	init_buildins_list(&mini);
	
// 	int i = -1;
// 	while (mini.list[++i])
// 	{
// 		printf("%s\n", mini.list[i]);
// 	}
// }
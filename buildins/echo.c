/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 15:38:56 by rabustam          #+#    #+#             */
/*   Updated: 2022/11/19 17:31:47 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* 
PROTÓTIPO ECHO - OBSERVAÇÕES:

1. Não acredito que ele mesmo printe a saída, fiz apenas para visualizar,
enquanto não temos o executor de fato. Isso por conta dos redirecionamentos
que ainda não tratei.

2. O retordo dele provavelmente será (char *), aqui está como int apenas
pra que eu visualizasse caso ocorresse erro de alocação.

3. Essa versão do protótipo já está Funcionando, na Norma e Sem Vazamentos.
*/

int	is_operator(char *token)
{
	size_t	len;

	len = ft_strlen(token);
	if (!ft_strncmp(token, "|", len))
		return (1);
	if (!ft_strncmp(token, ">", len))
		return (1);
	if (!ft_strncmp(token, "<", len))
		return (1);
	if (!ft_strncmp(token, ">>", len))
		return (1);
	if (!ft_strncmp(token, "<<", len))
		return (1);
	return (0);
}

char	*handle_quotes(char *token)
{
	char	*ret;

	ret = NULL;
	if (token[0] == '\"')
		ret = ft_strtrim(token, "\"");
	else if (token[0] == '\'')
		ret = ft_strtrim(token, "\'");
	return (ret);
}

int	n_cmds(t_token *token)
{
	int		n;
	t_token	*temp;

	temp = token;
	n = 0;
	while (temp && !is_operator(temp->cmd))
	{
		n++;
		temp = temp->next;
	}
	return (n);
}

char	**build_print(t_token *token, int len)
{
	int		i;
	char	**ret;
	char	*fr;
	t_token	*temp;

	ret = malloc(sizeof(char *) * (len + 1));
	if (!ret)
		return (NULL);
	ret[len] = NULL;
	i = -1;
	temp = token;
	while (++i < len)
	{
		ret[i] = ft_strdup(temp->cmd);
		fr = ret[i];
		if (ret[i][0] == '\'' || ret[i][0] == '\"')
		{
			ret[i] = handle_quotes(ret[i]);
			free(fr);
		}
		temp = temp->next;
	}
	return (ret);
}

int	echo(t_token *token)
{
	int		i;
	int		line_break;
	char	**print;

	line_break = 1;
	i = n_cmds(token);
	print = build_print(token, i);
	if (!print)
		return (-1);
	i = -1;
	while (print[++i])
	{
		if (!ft_strncmp(print[i], "-n", ft_strlen(print[i])))
			line_break = 0;
		else if (print[i + 1])
			printf("%s ", print[i]);
		else
			printf("%s", print[i]);
	}
	if (line_break)
		printf("\n");
	free_list(print);
	return (0);
}

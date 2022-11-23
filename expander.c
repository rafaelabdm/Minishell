/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:14:12 by rabustam          #+#    #+#             */
/*   Updated: 2022/11/23 03:59:53 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

//tentei usar a sua mas tava dando problema de memória
//então copiei rs, mas alterei pra funfar aqui
char	*ft_mattstr_copy(char **mat)
{
	char	*str;
	char	*temp;
	int		i;

	str = ft_strdup(mat[0]);
	i = 0;
	while (mat[++i])
	{
		temp = str;
		str = ft_strjoin(temp, mat[i]);
		free(temp);
	}
	free_list(mat);
	return (str);
}

int	count_expansions(char *cmd)
{
	int	i;

	i = 0;
	while (*cmd)
	{
		if (*cmd == '$')
			i++;
		cmd++;
	}
	return (i);
}

char	*get_envp(char *cmd, char **envp)
{
	char	*ret;
	int		len;

	ret = cmd;
	cmd++;
	if (*cmd == '{')
	{
		cmd++;
		len = ft_strlen(cmd) - 1;
	}
	else
		len = ft_strlen(cmd);
	while (*envp)
	{
		if (!ft_strncmp(cmd, *envp, len))
		{
			free(ret);
			return (ft_strdup(*envp + len + 2));
		}
		envp++;
	}
	free(ret);
	return (ft_strdup(""));
}

char	*expand(char *cmd, char **envp)
{
	char	**hold_str;
	int		ex;
	int		start;
	int		end;

	if (cmd[0] == '\'')
		return (NULL);
	ex = (count_expansions(cmd) * 2) + 2;
	hold_str = malloc(sizeof(char *) * ex);
	if (!hold_str)
		return (NULL);
	hold_str[ex - 1] = NULL;
	ex = 0;
	start = 0;
	end = -1;
	while (cmd[++end])
	{
		if (cmd[end] == '$')
		{
			hold_str[ex++] = ft_substr(cmd, start, end - start);
			start = end;
		}
		else if (cmd[start] == '$' && !ft_isalnum(cmd[end]) && cmd[end] != '{')
		{
			hold_str[ex++] = get_envp(ft_substr(cmd, start, end - start), envp);
			if (cmd[end] == '}')
				end++;
			start = end;
		}
	}
	hold_str[ex++] = ft_substr(cmd, start, end - start);
	if (hold_str[ex])
		hold_str[ex] = NULL;
	return (ft_mattstr_copy(hold_str));
}

void	expander(t_token **head, char **envp)
{
	char	*temp;
	t_token	*token;

	token = *head;
	while (token)
	{
		if (ft_strchr(token->cmd, '$'))
		{
			temp = token->cmd;
			token->cmd = expand(token->cmd, envp);
			if (token->cmd == NULL)
				token->cmd = temp;
			else
				free(temp);
		}
		token = token->next;
	}
}

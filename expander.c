/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:14:12 by rabustam          #+#    #+#             */
/*   Updated: 2022/11/29 16:38:38 by rabustam         ###   ########.fr       */
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
			return (ft_strdup(*envp + len + 1));
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
	int		quotes;

	ex = (count_expansions(cmd) * 2) + 2;
	hold_str = malloc(sizeof(char *) * ex);
	if (!hold_str)
		return (NULL);
	hold_str[ex - 1] = NULL;
	ex = 0;
	start = 0;
	end = -1;
	quotes = 0;
	while (cmd[++end])
	{
		quotes = check_quotes(cmd[end], quotes);
		if (cmd[end] == '$' && quotes != 2)
		{
			hold_str[ex++] = ft_substr(cmd, start, end - start);
			start = end;
		}
		else if (cmd[start] == '$' && cmd[end] != '{' && !ft_isalnum(cmd[end])  && quotes != 2)
		{
			hold_str[ex++] = get_envp(ft_substr(cmd, start, end - start), envp);
			if (cmd[end] == '}')
				end++;
			start = end;
		}
	}
	if (cmd[start] == '$')
		hold_str[ex++] = get_envp(ft_substr(cmd, start, end - start), envp);
	else
		hold_str[ex++] = ft_substr(cmd, start, end - start);
	hold_str[ex] = NULL;
	return (ft_mattstr_copy(hold_str));
}

char	*expand_quotes(char *cmd)
{
	int	i;
	int	quotes;
	char	**ret;
	
	i = -1;
	quotes = 0;
	while (cmd[++i])
	{
		quotes = check_quotes(cmd[i], quotes);
		if ((cmd[i] == '\'' || cmd[i] == '\"') && !quotes)
			cmd[i] = SEP;
		else if ((cmd[i] == '\'' && quotes == 2) ||\
		(cmd[i] == '\"' && quotes == 1))
			cmd[i] = SEP;
	}
	ret = ft_split(cmd, SEP);
	if (!*ret)
	{
		free_list(ret);
		return (ft_strdup(""));
	}
	return (ft_mattstr_copy(ret));
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
		temp = token->cmd;
		token->cmd = expand_quotes(token->cmd);
		free(temp);
		token = token->next;
	}
}

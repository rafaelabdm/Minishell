/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 09:43:20 by rabustam          #+#    #+#             */
/*   Updated: 2022/12/28 09:43:20 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1)
		s1 = ft_calloc(1, sizeof(char));
	if (!s1 || !s2)
		return (NULL);
	str = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof (char));
	if (!str)
		return (0);
	i = -1;
	j = 0;
	while (s1[++i])
		str[i] = s1[i];
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	s2 = free_ptr(s2);
	s1 = free_ptr(s1);
	return (str);
}

static char	*number_to_string(int n)
{
	char	*errnum;
	int		i;
	int		temp;

	temp = n;
	if (!temp)
		return (ft_strdup("0"));
	i = 0;
	while (temp)
	{
		temp = temp / 10;
		i++;
	}
	errnum = ft_calloc(i + 1, sizeof(char));
	while (n)
	{
		errnum[i - 1] = (n % 10) + 48;
		n = n / 10;
		i--;
	}
	return (errnum);
}

static char	*exit_status(t_mini *ms, char *f, char *cmd)
{
	char	*ret;

	ret = NULL;
	if (!*cmd)
	{
		f = free_ptr(f);
		return (ft_strdup("$"));
	}
	if (cmd && cmd[1])
		ret = ft_strdup(++cmd);
	f = free_ptr(f);
	return (ft_strjoin_gnl(number_to_string(ms->error), ret));
}

int	find_equalsing(char *var)
{
	int	i;

	i = 0;
	if (!var)
		return (0);
	while (var[i] && var[i] != '=')
		i++;
	return (i);
}

char	*get_envp(t_mini *ms, char *cmd, char **envp)
{
	char	*ret;
	int		len;
	int		var_len;

	ret = cmd;
	cmd++;
	if (*cmd == '{')
	{
		cmd++;
		len = ft_strlen(cmd);
	}
	else
		len = ft_strlen(cmd);
	if (*cmd == '?' || len == 0)
		return (exit_status(ms, ret, cmd));
	while (*envp)
	{
		var_len = find_equalsing(*envp);
		if (!ft_strncmp(cmd, *envp, var_len))
		{
			ret = free_ptr(ret);
			return (ft_strdup(*envp + len + 1));
		}
		envp++;
	}
	ret = free_ptr(ret);
	return (ft_strdup(""));
}

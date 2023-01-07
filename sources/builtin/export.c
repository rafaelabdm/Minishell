/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 14:45:43 by rapdos-s          #+#    #+#             */
/*   Updated: 2023/01/04 14:45:43 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_var_pos(char *var, char **envp)
{
	char	*var_temp;
	int		var_len;
	int		var_pos;

	var_len = ft_strchr (var, '=') - var;
	var_pos = 0;
	var_temp = ft_calloc (var_len + 2, sizeof (char));
	ft_strlcpy (var_temp, var, var_len + 2);
	var_temp[var_len] = '=';
	var_temp[var_len + 1] = '\0';
	while (envp[var_pos] && ft_strncmp (envp[var_pos], var_temp, var_len + 1))
		var_pos++;
	var_temp = free_ptr (var_temp);
	return (var_pos);
}

static void	update_var(char *var, int var_pos, char ***envp)
{
	char	**envp_temp;

	if (!envp[0][var_pos])
	{
		envp_temp = ft_calloc (var_pos + 2, sizeof (char *));
		envp_temp[var_pos] = ft_strdup (var);
		while (var_pos--)
			envp_temp[var_pos] = ft_strdup (envp[0][var_pos]);
		*envp = free_mat (*envp);
		*envp = envp_temp;
	}
	else
	{
		envp[0][var_pos] = free_ptr (envp[0][var_pos]);
		envp[0][var_pos] = ft_strdup (var);
	}
}

static int	valid_var(char *var)
{
	int	i;
	int	ret;

	ret = 1;
	if (!var || (var && var[0] == '='))
		ret = 0;
	if (ft_isdigit (var[0]))
		ret = 0;
	i = 0;
	while (var[i] && var[i] != '=')
	{
		if (var[i] != '_' && !ft_isalnum(var[i]))
			ret = 0;
		i++;
	}
	return (ret);
}

void	ft_export(t_mini *ms, char **cmd, char ***envp)
{
	int	i;
	int	var_pos;

	i = 1;
	if (!cmd[1])
		ft_env(ms, cmd, envp);
	while (cmd[i])
	{
		if (valid_var (cmd[i]) && ft_strchr (cmd[i], '='))
		{
			var_pos = get_var_pos (cmd[i], *envp);
			update_var (cmd[i], var_pos, envp);
			ms -> error = 0;
		}
		else if (!valid_var (cmd[i]))
		{
			ft_putstr_fd(PROMPT_MSG": export: ", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			ms -> error = 42;
		}
		else
			ms -> error = 0;
		i++;
	}
}

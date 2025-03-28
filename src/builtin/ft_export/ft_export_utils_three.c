/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils_three.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 06:46:48 by marvin            #+#    #+#             */
/*   Updated: 2025/03/21 01:59:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_new_env_var(t_shell *shell, char *new_var)
{
	int		cnt;
	char	**new_env;
	int		j;

	cnt = count_array(shell->env);
	new_env = malloc((cnt + 2) * sizeof(char *));
	if (!new_env)
		return ;
	j = 0;
	while (j < cnt)
	{
		new_env[j] = shell->env[j];
		j++;
	}
	new_env[cnt] = ft_strdup(new_var);
	if (!new_env)
		handle_malloc_error();
	new_env[cnt + 1] = NULL;
	free(shell->env);
	shell->env = new_env;
}

void	update_env_var(t_shell *shell, char *var_name, char *new_var)
{
	if (!update_existing_env(shell, var_name, new_var))
		add_new_env_var(shell, new_var);
}

void	remove_from_export(t_shell *shell, char *var_name)
{
	int	i;
	int	cnt;
	int	pos;

	cnt = count_array(shell->exp);
	i = 0;
	while (i < cnt)
	{
		if (ft_strcmp(var_name, shell->exp[i]) == 0)
		{
			pos = i;
			while (pos < cnt - 1)
			{
				shell->exp[pos] = shell->exp[pos + 1];
				pos++;
			}
			shell->exp[cnt - 1] = NULL;
			break ;
		}
		i++;
	}
}

int	export_exists(t_shell *shell, char *var)
{
	int		i;
	char	*name;

	i = 0;
	while (shell->env && shell->env[i])
	{
		name = get_name_from_env(shell->env[i]);
		if (ft_strcmp(var, name) == 0)
		{
			free(name);
			return (1);
		}
		free(name);
		i++;
	}
	i = 0;
	while (shell->exp && shell->exp[i])
	{
		if (ft_strcmp(var, shell->exp[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	add_to_export(t_shell *shell, char *var)
{
	int		cnt;
	char	**new_exp;
	int		j;

	if (export_exists(shell, var))
		return ;
	cnt = count_array(shell->exp);
	new_exp = malloc((cnt + 2) * sizeof(char *));
	if (!new_exp)
		return ;
	j = 0;
	while (j < cnt)
	{
		new_exp[j] = shell->exp[j];
		j++;
	}
	new_exp[cnt] = ft_strdup(var);
	if (!new_exp || !new_exp[0])
		return ;
	new_exp[cnt + 1] = NULL;
	if (shell->exp)
		free(shell->exp);
	shell->exp = new_exp;
}

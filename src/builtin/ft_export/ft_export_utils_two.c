/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils_two.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 06:46:16 by marvin            #+#    #+#             */
/*   Updated: 2025/03/12 06:46:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**merge_lists(t_shell *shell)
{
	char	**merged;
	int		total;
	int		j;

	total = count_array(shell->env) + count_array(shell->exp);
	merged = malloc((total + 1) * sizeof(char *));
	if (!merged)
		return (NULL);
	j = copy_array(shell->env, merged, 0);
	j = copy_array(shell->exp, merged, j);
	merged[j] = NULL;
	return (merged);
}

void	sort_array(char **arr, int total)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < total)
	{
		j = i + 1;
		while (j < total)
		{
			if (ft_strcmp(arr[i], arr[j]) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_array(char **arr)
{
	int		i;
	char	*eq;
	int		len;

	i = 0;
	while (arr[i])
	{
		write(1, "declare -x ", 11);
		eq = ft_strchr(arr[i], '=');
		if (eq)
		{
			len = eq - arr[i];
			write(1, arr[i], len);
			write(1, "=\"", 2);
			write(1, eq + 1, ft_strlen(eq + 1));
			write(1, "\"\n", 2);
		}
		else
		{
			write(1, arr[i], ft_strlen(arr[i]));
			write(1, "\n", 1);
		}
		i++;
	}
}

void	print_export_list(t_shell *shell)
{
	char	**merged;
	int		total;
	int		i;

	merged = merge_lists(shell);
	if (!merged)
		return ;
	total = count_array(merged);
	sort_array(merged, total);
	print_array(merged);
	i = 0;
	while (merged[i])
	{
		free(merged[i]);
		i++;
	}
	free(merged);
}

int	update_existing_env(t_shell *shell, char *var_name, char *new_var)
{
	int		i;
	char	*env_name;

	i = 0;
	while (shell->env && shell->env[i])
	{
		env_name = get_name_from_env(shell->env[i]);
		if (ft_strcmp(var_name, env_name) == 0)
		{
			free(shell->env[i]);
			shell->env[i] = ft_strdup(new_var);
			if (!shell->env)
				handle_malloc_error();
			free(env_name);
			return (1);
		}
		free(env_name);
		i++;
	}
	return (0);
}

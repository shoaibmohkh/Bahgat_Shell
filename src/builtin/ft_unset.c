/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 07:34:10 by marvin            #+#    #+#             */
/*   Updated: 2025/03/15 07:33:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_name_unset(const char *str)
{
	int		i;
	int		j;
	char	*name;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	name = malloc(i + 1);
	if (!name)
	{
		print_error("minishell", "unset", "Memory allocation failed");
		return (NULL);
	}
	j = 0;
	while (j < i)
	{
		name[j] = str[j];
		j++;
	}
	name[i] = '\0';
	return (name);
}

static int	find_env_index(t_shell *test, char *arg, int *error_flag)
{
	int		j;
	char	*env_name;

	j = 0;
	while (test->env && test->env[j])
	{
		env_name = get_name_unset(test->env[j]);
		if (!env_name)
		{
			*error_flag = 1;
			return (-1);
		}
		if (ft_strcmp(env_name, arg) == 0)
		{
			free(env_name);
			return (j);
		}
		free(env_name);
		j++;
	}
	return (-1);
}

static void	unset_env(t_shell *test, char *arg, int *error_flag)
{
	int	index;
	int	k;

	index = find_env_index(test, arg, error_flag);
	if (index < 0)
		return ;
	free(test->env[index]);
	k = index;
	while (test->env[k + 1])
	{
		test->env[k] = test->env[k + 1];
		k++;
	}
	test->env[k] = NULL;
}

static void	unset_exp(t_shell *test, char *arg)
{
	int	j;
	int	k;

	j = 0;
	while (test->exp && test->exp[j])
	{
		if (ft_strcmp(test->exp[j], arg) == 0)
		{
			free(test->exp[j]);
			k = j;
			while (test->exp[k + 1])
			{
				test->exp[k] = test->exp[k + 1];
				k++;
			}
			test->exp[k] = NULL;
			return ;
		}
		j++;
	}
}

void	ft_unset(t_shell *test, char **args)
{
	int	error_flag;
	int	i;

	error_flag = 0;
	if (!args[1])
		return ;
	i = 1;
	while (args[i])
	{
		unset_env(test, args[i], &error_flag);
		unset_exp(test, args[i]);
		i++;
	}
	if (error_flag)
	{
		print_error("minishell", "unset",
			"Error occurred while unsetting variable");
		test->exit_status = 1;
	}
	else
		test->exit_status = 0;
}

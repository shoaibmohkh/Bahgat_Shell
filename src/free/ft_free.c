/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:29:43 by shoaib            #+#    #+#             */
/*   Updated: 2025/03/22 03:05:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_2d(char **ar)
{
	int	i;

	if (!ar)
		return ;
	i = 0;
	while ((ar)[i])
	{
		free((ar)[i]);
		i++;
	}
	free(ar);
}

void	free_3d(char ***ar)
{
	int	i;

	if (!ar || !*ar)
		return ;
	i = 0;
	while ((ar)[i])
	{
		free_2d(((ar)[i]));
		i++;
	}
	free(ar);
}

void	free_child_resources(t_shell *shell)
{
	if (shell->input)
		free(shell->input);
	if (shell->input_splitted)
		free_2d(shell->input_splitted);
	if (shell->split_the_split)
		free_3d(shell->split_the_split);
	if (shell->command)
		free(shell->command);
	free_dir_operate(shell);
	null_and_zero(shell);
}

void	null_and_zero(t_shell *shell)
{
	shell->input = NULL;
	shell->input_splitted = NULL;
	shell->split_the_split = NULL;
	shell->command = NULL;
	shell->dir = NULL;
	shell->operate = NULL;
	shell->command_count = 0;
	shell->dir_count = 0;
	shell->operate_count = 0;
	shell->count_pipe = 0;
}

void	free_shell(t_shell *shell, int f, int child)
{
	if (!shell)
		return ;
	if (child)
		free_child_resources(shell);
	if (f)
	{
		if (shell->env)
		{
			free_2d(shell->env);
			shell->env = NULL;
		}
		if (shell->old_pwd)
		{
			free(shell->old_pwd);
			shell->old_pwd = NULL;
		}
		if (shell->exp)
		{
			free_2d(shell->exp);
			shell->exp = NULL;
		}
		shell->name_program = NULL;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:34:47 by sal-kawa          #+#    #+#             */
/*   Updated: 2025/03/21 00:01:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_target_directory(t_shell *shell, int i, char **target)
{
	*target = shell->command[i][1];
	if (check_dir(*target) != 1)
	{
		if (check_dir(*target) == 3)
			print_error(shell->name_program, "cd", "Permission Denied");
		else
			print_error(shell->name_program, "cd", "no such file or directory");
		shell->exit_status = 1;
		*target = NULL;
	}
}

void	get_directory(t_shell *shell, int i, char **target)
{
	char	*home;

	home = get_env_value(shell, "HOME");
	if (!shell->command[i][1] || ft_strcmp(shell->command[i][1], "~") == 0
		|| ft_strcmp(shell->command[i][1], "--") == 0)
	{
		if (!home)
		{
			print_error(shell->name_program, "cd", "HOME not set");
			shell->exit_status = 1;
			*target = NULL;
			return ;
		}
		*target = home;
	}
	else
		get_target_directory(shell, i, target);
}

void	change_directory(t_shell *shell, char *target)
{
	char	*cwd_after;

	get_old_pwd(shell);
	if (chdir(target) != 0)
	{
		print_error(shell->name_program, "cd", strerror(errno));
		shell->exit_status = 1;
		return ;
	}
	cwd_after = getcwd(NULL, 0);
	if (!cwd_after)
	{
		print_error(shell->name_program, "cd",
			"error retrieving current directory: getcwd:");
		print_error(NULL, NULL,
			"cannot access parent directories: No such file or directory");
		shell->exit_status = 0;
		return ;
	}
	update_pwd(shell);
	shell->exit_status = 0;
	free(cwd_after);
}

void	ft_cd(t_shell *shell, int i)
{
	char	*target;

	target = NULL;
	if (shell->command[i][1] != NULL && shell->command[i][2] != NULL)
	{
		print_error(shell->name_program, "cd", "too many arguments");
		shell->exit_status = 1;
		return ;
	}
	get_directory(shell, i, &target);
	if (!target && shell->command[i][1] && ft_strcmp(shell->command[i][1],
			"..") != 0)
	{
		shell->exit_status = 1;
		return ;
	}
	change_directory(shell, target);
}

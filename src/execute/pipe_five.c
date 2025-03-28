/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_five.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 06:47:50 by sal-kawa          #+#    #+#             */
/*   Updated: 2025/03/21 00:47:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_handle_builtin(t_shell *shell, int i, t_pipe_vars *vars)
{
	if (is_builtin_funcion(shell, i))
	{
		run_builtin_function(shell, i, vars->out_fd);
		if (vars->in_fd != STDIN_FILENO)
			close(vars->in_fd);
		if (vars->out_fd != STDOUT_FILENO)
			close(vars->out_fd);
		if (ft_strcmp(shell->command[i][0], "exit") == 0)
		{
			ft_exit(shell, i);
			free_shell(shell, 1, 1);
			e_exit(shell, shell->exit_status);
		}
		free_shell(shell, 1, 1);
		e_exit(shell, shell->exit_status);
	}
}

void	child_check_directory_errors_two_if(t_shell *shell, char *path)
{
	int	dir_check;

	dir_check = check_dir(path);
	if (dir_check == 1 || dir_check == 3)
	{
		print_error(shell->name_program, path, "is a directory");
		free_shell(shell, 1, 1);
		e_exit(shell, 126);
	}
	else if (dir_check == 2)
	{
		print_error(shell->name_program, path, "Not a directory");
		free_shell(shell, 1, 1);
		e_exit(shell, 126);
	}
	else
	{
		print_error(shell->name_program, path, "No such file or directory");
		free_shell(shell, 1, 1);
		e_exit(shell, 127);
	}
}

void	child_check_directory_errors_two(t_shell *shell, char **argv)
{
	int	len;

	if (!argv || !argv[0])
		return ;
	len = ft_strlen(argv[0]);
	if (len == 0)
		return ;
	if (argv[0][len - 1] == '/')
	{
		argv[0][len - 1] = '\0';
		child_check_directory_errors_two_if(shell, argv[0]);
	}
}

void	execute_command(t_shell *shell, char **argv, char *cmd_path)
{
	if (check_dir(cmd_path) == 1)
	{
		print_error(shell->name_program, argv[0], "Is a directory");
		free(cmd_path);
		free_shell(shell, 1, 1);
		e_exit(shell, 126);
	}
	argv[0] = cmd_path;
	if (execve(cmd_path, argv, shell->env) == -1)
	{
		print_error(shell->name_program, argv[0], strerror(errno));
		free(cmd_path);
		free_shell(shell, 1, 1);
		e_exit(shell, 127);
	}
}

void	child_exec_command(t_shell *shell, char **argv)
{
	char	*cmd_path;

	if (!argv || !argv[0])
		free_for_args(shell);
	cmd_path = getpath(shell, argv);
	if (!cmd_path || ft_strcmp(argv[0], "..") == 0
		|| ft_strcmp(argv[0], ".") == 0)
	{
		if (ft_strcmp(argv[0], ".") == 0)
		{
			print_error(shell->name_program, argv[0],
				"filename argument required");
			free(cmd_path);
			free_shell(shell, 1, 1);
			e_exit(shell, 2);
		}
		else
		{
			print_error(shell->name_program, argv[0], "Command not found");
			free(cmd_path);
			free_shell(shell, 1, 1);
			e_exit(shell, 127);
		}
	}
	execute_command(shell, argv, cmd_path);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:59:18 by sal-kawa          #+#    #+#             */
/*   Updated: 2025/03/22 08:57:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_for_args(t_shell *shell)
{
	free_shell(shell, 1, 1);
	e_exit(shell, 127);
}

void	child_process(t_shell *shell, int i, t_pipe_vars *vars, char **argv)
{
	child_setup_redirfds(shell, vars);
	child_close_fds(vars);
	child_handle_builtin(shell, i, vars);
	child_check_directory_errors_one(shell, i, argv);
	child_check_directory_errors_two(shell, argv);
	child_exec_command(shell, argv);
}

void	process_pipeline_iteration(t_shell *shell, int i, t_pipe_vars *vars)
{
	char	**argv;

	argv = shell->command[i];
	setup_pipeline_iteration(shell, i, vars);
	if (!vars->redir_success)
		return ;
	if (bulitin_run_command_execute(shell, i, vars))
	{
		free_shell(shell, 0, 1);
		return ;
	}
	vars->pipe_created = 0;
	if (i < shell->count_pipe)
		create_pipess(shell, i, vars);
	create_fork(shell, vars);
	if (vars->pid == 0)
		child_process(shell, i, vars, argv);
	close_after_fork(vars);
}

void	pipeline_with_command(t_shell *shell)
{
	t_pipe_vars	vars;

	ft_bzero(&vars, sizeof(t_pipe_vars));
	vars.prev_fd = -1;
	vars.i = 0;
	while (vars.i == 0 || vars.i <= shell->count_pipe)
	{
		process_pipeline_iteration(shell, vars.i, &vars);
		vars.i++;
	}
	wait_for_children(shell, vars.pid);
	if (shell->flag_here)
	{
		shell->exit_status = 130;
		shell->flag_here = 0;
	}
}

void	execute_pipes_redir(t_shell *shell)
{
	if (!shell || !shell->split_the_split)
	{
		perror("Error: Invalid shell structure or environment");
		return ;
	}
	if (shell->command_count < 1)
		pipeline_no_command(shell);
	else
		pipeline_with_command(shell);
}

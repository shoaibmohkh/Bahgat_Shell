/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 06:46:27 by sal-kawa          #+#    #+#             */
/*   Updated: 2025/03/22 08:57:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_pipeline_redirections(t_shell *shell, int i, t_pipe_vars *vars)
{
	vars->b = 0;
	while (shell->dir[i][vars->b])
	{
		if (!get_redirections(shell->dir[i][vars->b],
			shell->operate[i][vars->b], vars,
			shell))
		{
			shell->exit_status = 1;
			vars->redir_success = 0;
			break ;
		}
		vars->b++;
	}
}

void	execute_builtin_cleanup(t_pipe_vars *vars)
{
	if (vars->in_fd != STDIN_FILENO)
	{
		dup2(vars->in_fd, STDIN_FILENO);
		close(vars->in_fd);
	}
	if (vars->out_fd != STDOUT_FILENO)
	{
		dup2(vars->out_fd, STDOUT_FILENO);
		close(vars->out_fd);
	}
}

int	bulitin_run_command_execute(t_shell *shell, int i, t_pipe_vars *vars)
{
	int	v;

	if (shell->command_count == 1 && shell->count_pipe == 0 && shell->command
		&& shell->command[0])
	{
		if (is_builtin_funcion(shell, i))
		{
			run_builtin_function(shell, i, vars->out_fd);
			if (ft_strcmp(shell->command[i][0], "exit") == 0)
			{
				v = ft_exit(shell, i);
				if (v)
				{
					free_shell(shell, 1, 1);
					e_exit(shell, shell->exit_status);
				}
			}
			free_shell(shell, 0, 1);
			execute_builtin_cleanup(vars);
			return (1);
		}
	}
	return (0);
}

void	create_pipess(t_shell *shell, int i, t_pipe_vars *vars)
{
	if (i < shell->count_pipe)
	{
		if (pipe(vars->pipe_fd) == -1)
		{
			perror("pipe");
			free_shell(shell, 1, 1);
			e_exit(shell, 1);
		}
		vars->pipe_created = 1;
	}
}

int	create_fork(t_shell *shell, t_pipe_vars *vars)
{
	vars->pid = fork();
	if (vars->pid < 0)
	{
		perror("fork");
		free_shell(shell, 1, 1);
		e_exit(shell, 1);
	}
	return (vars->pid);
}

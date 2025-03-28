/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_four.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 06:47:10 by sal-kawa          #+#    #+#             */
/*   Updated: 2025/03/21 17:27:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_after_fork(t_pipe_vars *vars)
{
	if (vars->in_fd != STDIN_FILENO)
		close(vars->in_fd);
	if (vars->out_fd != STDOUT_FILENO)
		close(vars->out_fd);
	if (vars->prev_fd != -1)
		close(vars->prev_fd);
	if (vars->pipe_created)
	{
		close(vars->pipe_fd[1]);
		vars->prev_fd = vars->pipe_fd[0];
	}
	else
		vars->prev_fd = -1;
}

void	wait_for_children(t_shell *shell, int pid)
{
	int	wstatus;
	int	cpid;

	cpid = 1;
	while (cpid > 0)
	{
		cpid = wait(&wstatus);
		if (cpid == pid)
		{
			if (WIFEXITED(wstatus))
				shell->exit_status = WEXITSTATUS(wstatus);
			else
				shell->exit_status = 128 + WTERMSIG(wstatus);
		}
	}
}

void	child_setup_redirfds(t_shell *shell, t_pipe_vars *vars)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (!vars->redir_success)
	{
		if (vars->in_fd != STDIN_FILENO)
			close(vars->in_fd);
		if (vars->out_fd != STDOUT_FILENO)
			close(vars->out_fd);
		free_shell(shell, 1, 1);
		e_exit(shell, 1);
	}
}

void	child_check_directory_errors_one(t_shell *shell, int i, char **argv)
{
	if (!shell->command[i] || !shell->command[i][0])
		return ;
	if (ft_strcmp(shell->command[i][0], "/") == 0
		&& shell->command[i][1] == NULL)
	{
		print_error(shell->name_program, argv[0], "Is a directory");
		free_shell(shell, 1, 1);
		e_exit(shell, 126);
	}
}

void	child_close_fds(t_pipe_vars *vars)
{
	if (vars->in_fd != STDIN_FILENO)
	{
		dup2(vars->in_fd, STDIN_FILENO);
		close(vars->in_fd);
	}
	if (vars->pipe_created)
	{
		if (vars->out_fd == STDOUT_FILENO)
			vars->out_fd = vars->pipe_fd[1];
	}
	if (vars->out_fd != STDOUT_FILENO)
	{
		dup2(vars->out_fd, STDOUT_FILENO);
		close(vars->out_fd);
	}
	if (vars->prev_fd != -1)
		close(vars->prev_fd);
	if (vars->pipe_created)
	{
		close(vars->pipe_fd[0]);
		close(vars->pipe_fd[1]);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_two.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-kawa <sal-kawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 06:44:50 by sal-kawa          #+#    #+#             */
/*   Updated: 2025/03/13 06:40:34 by sal-kawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipeline_no_command_redier(t_shell *shell, t_pipe_vars *vars)
{
	vars->b = 0;
	while (shell->dir[vars->a][vars->b])
	{
		if (!get_redirections(shell->dir[vars->a][vars->b],
			shell->operate[vars->a][vars->b],
			vars, shell))
		{
			shell->exit_status = 1;
			return ;
		}
		if (vars->in_fd != STDIN_FILENO)
			close(vars->in_fd);
		if (vars->out_fd != STDOUT_FILENO)
			close(vars->out_fd);
		dup2(vars->saved_stdin, STDIN_FILENO);
		dup2(vars->saved_stdout, STDOUT_FILENO);
		vars->b++;
	}
}

void	pipeline_no_command_pipe_valid(t_shell *shell, t_pipe_vars *vars)
{
	vars->in_fd = STDIN_FILENO;
	vars->out_fd = STDOUT_FILENO;
	vars->a = 0;
	shell->dir_count -= 1;
	while (shell->dir_count--)
	{
		pipeline_no_command_redier(shell, vars);
		vars->a++;
	}
}

void	pipeline_no_command_run(t_shell *shell, t_pipe_vars *vars)
{
	if (shell->count_pipe)
	{
		if (shell->count_pipe < shell->dir_count)
			pipeline_no_command_pipe_valid(shell, vars);
		else
		{
			write(2, "syntax error\n", 13);
			free_shell(shell, 0, 1);
			close(vars->saved_stdin);
			close(vars->saved_stdout);
			return ;
		}
	}
	else
	{
		vars->a = 0;
		pipeline_no_command_redier(shell, vars);
	}
}

void	pipeline_no_command(t_shell *shell)
{
	t_pipe_vars	vars;

	ft_bzero(&vars, sizeof(t_pipe_vars));
	vars.in_fd = STDIN_FILENO;
	vars.out_fd = STDOUT_FILENO;
	vars.saved_stdin = dup(STDIN_FILENO);
	vars.saved_stdout = dup(STDOUT_FILENO);
	pipeline_no_command_run(shell, &vars);
	close(vars.saved_stdin);
	close(vars.saved_stdout);
	wait_for_children(shell, vars.pid);
	if (shell->flag_here)
	{
		shell->exit_status = 130;
		shell->flag_here = 0;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:02:34 by sal-kawa          #+#    #+#             */
/*   Updated: 2025/03/21 01:06:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_input_redirection(char *filename, t_pipe_vars *vars)
{
	if (vars->in_fd != STDIN_FILENO)
		close(vars->in_fd);
	if (check_dir(filename) == 0)
	{
		printf("error: %s does not exist\n", filename);
		return (0);
	}
	vars->in_fd = open(filename, O_RDONLY);
	if (vars->in_fd < 0)
	{
		perror("error opening input file");
		return (0);
	}
	return (1);
}

int	handle_output_redirection(const char *filename, t_pipe_vars *vars,
		int append)
{
	if (vars->out_fd != STDOUT_FILENO)
		close(vars->out_fd);
	if (append)
		vars->out_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		vars->out_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (vars->out_fd < 0)
	{
		perror("error opening output file");
		return (0);
	}
	return (1);
}

int	check_operator(char *filename, char *operator, t_pipe_vars *vars,
		t_shell *test)
{
	int	success;

	success = 1;
	if (ft_strcmp(operator, "<") == 0)
		success = handle_input_redirection(filename, vars);
	else if (ft_strcmp(operator, ">") == 0)
		success = handle_output_redirection(filename, vars, 0);
	else if (ft_strcmp(operator, ">>") == 0)
		success = handle_output_redirection(filename, vars, 1);
	else if (ft_strcmp(operator, "<<") == 0)
		success = handle_here_doc(filename, &(vars->in_fd), test);
	else
	{
		perror("operator get_redirection error");
		success = 0;
	}
	return (success);
}

int	get_redirections(char *filename, char *operator, t_pipe_vars *vars,
		t_shell *test)
{
	int	success;

	if (!filename || !operator)
	{
		perror("error in redirection or file name");
		return (0);
	}
	success = check_operator(filename, operator, vars, test);
	if (!success || test->flag_here == 1)
	{
		if (vars->in_fd != STDIN_FILENO)
		{
			close(vars->in_fd);
			vars->in_fd = STDIN_FILENO;
		}
		if (vars->out_fd != STDOUT_FILENO)
		{
			close(vars->out_fd);
			vars->out_fd = STDOUT_FILENO;
		}
	}
	return (success);
}

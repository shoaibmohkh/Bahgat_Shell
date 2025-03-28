/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 07:35:17 by marvin            #+#    #+#             */
/*   Updated: 2025/03/22 07:37:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_only_whitespace(char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (!ft_isspace((unsigned char)*s))
			return (0);
		s++;
	}
	return (1);
}

int	check_pipe_syntax(t_shell *test)
{
	int	i;

	if (test->count_pipe)
	{
		i = 0;
		if (!test->input_splitted)
			return (0);
		while (test->input_splitted[i])
		{
			if (ft_strcmp(test->input_splitted[i], "|") == 0)
			{
				if (i == 0 || test->input_splitted[i + 1] == NULL
					|| test->input_splitted[i + 1][0] == '\0'
					|| (ft_strcmp(test->input_splitted[i + 1], "|") == 0))
				{
					print_error(test->name_program, NULL,
						"syntax error near unexpected token `newline'");
					test->exit_status = 2;
					return (0);
				}
			}
			i++;
		}
	}
	return (1);
}

void	check_command_count(t_shell *test)
{
	if (!test)
		return ;
	if (test->command_count == 0 && test->count_pipe == 0
		&& test->dir_count == 0)
	{
		if (msg_operate_error(test))
			test->exit_status = 2;
	}
	else
		execute_pipes_redir(test);
}

void	run_command(t_shell *test)
{
	if (!test)
		return ;
	if ((!test->command || !test->command[0] || !test->command[0][0])
		&& test->operate_count == 0 && test->count_pipe == 0
		&& test->dir_count == 0)
		return ;
	if (!check_pipe_syntax(test))
		return ;
	check_command_count(test);
	free_shell(test, 0, 1);
}

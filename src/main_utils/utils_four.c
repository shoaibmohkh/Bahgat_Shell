/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_four.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 07:48:27 by marvin            #+#    #+#             */
/*   Updated: 2025/03/22 07:46:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe_operate(t_shell *test)
{
	if (!test)
		return (0);
	if (test->dir_count != test->operate_count)
	{
		ft_printf("%s: syntax error near unexpected token `newline'\n",
			test->name_program);
		free_shell(test, 0, 1);
		test->exit_status = 2;
		return (0);
	}
	return (1);
}

void	execute_and_cleanup(t_shell *test)
{
	if (!test)
		return ;
	run_command(test);
	free_shell(test, 0, 1);
}

int	process_command_phase(t_shell *test)
{
	if (!test)
		return (2);
	expand_all_tokens(test);
	count_pipe(test);
	command_count(test);
	operate(test);
	dir(test);
	if (test->dir_count >= 1)
	{
		if (check_redirections(test))
		{
			test->exit_status = 2;
			return (2);
		}
	}
	if (!check_quotes(test))
		return (2);
	if (!check_pipe_operate(test))
		return (2);
	execute_and_cleanup(test);
	return (1);
}

int	check_quotes_utils(t_shell *test)
{
	ft_printf("%s: syntax error near unexpected token `newline'\n",
		test->name_program);
	free_shell(test, 0, 1);
	test->exit_status = 2;
	return (0);
}

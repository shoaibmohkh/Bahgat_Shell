/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_five.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:39:04 by sal-kawa          #+#    #+#             */
/*   Updated: 2025/03/22 07:35:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirection_error_sames(t_shell *test, int i)
{
	if (!test || !test->input)
		return (1);
	if (test->input[i + 1] == test->input[i])
	{
		if (test->input[i + 2] == test->input[i] || (test->input[i + 1] == '>'
				&& test->input[i] == '<') || (test->input[i + 1] == '<'
				&& test->input[i] == '>'))
		{
			printf("%s: syntax error near unexpected token",
				test->name_program);
			printf("'%c%c'\n", test->input[i], test->input[i + 1]);
			free_shell(test, 0, 1);
			test->exit_status = 22;
			return (1);
		}
	}
	return (0);
}

int	check_redirection_error_diffs(t_shell *test, int i)
{
	if (!test || !test->input)
		return (1);
	if ((test->input[i + 1] == '>' && test->input[i] == '<')
		|| (test->input[i + 1] == '<' && test->input[i] == '>'))
	{
		printf("%s: syntax error near unexpected token",
			test->name_program);
		printf("'%c%c'\n", test->input[i], test->input[i + 1]);
		free_shell(test, 0, 1);
		test->exit_status = 22;
		return (1);
	}
	return (0);
}

int	process_redirectionss(t_shell *test)
{
	int	i;

	if (!test || !test->input)
		return (1);
	i = 0;
	while (test->input[i])
	{
		if (is_redirection_operatora(test->input[i]))
		{
			if (test->input[i] == '<' || test->input[i] == '>')
			{
				if (check_redirection_error_sames(test, i))
					return (1);
				else if (check_redirection_error_diffs(test, i))
					return (1);
			}
		}
		i++;
	}
	return (0);
}

int	input_phase(t_shell *test)
{
	int	ret_input;

	if (!test)
		return (2);
	ret_input = handle_input(test);
	if (ret_input == 0)
		return (0);
	if (ret_input == 2)
		return (2);
	if (!split_input(test))
		return (2);
	return (1);
}

int	command_phase(t_shell *test)
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
		if (process_redirectionss(test))
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

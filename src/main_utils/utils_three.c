/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 07:46:00 by marvin            #+#    #+#             */
/*   Updated: 2025/03/22 07:44:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection_operatora(char op)
{
	return (op == '>' || op == '<');
}

int	check_mixed_operator_case(t_shell *test, int i)
{
	if (!test || !test->input || i < 0 || !test->input[i + 1])
		return (0);
	if ((test->input[i + 1] == '>' && test->input[i] == '<')
		|| (test->input[i + 1] == '<' && test->input[i] == '>'))
	{
		printf("%s: syntax error near unexpected token '%c%c'\n",
			test->name_program,
			test->input[i],
			test->input[i + 1]);
		free_shell(test, 0, 1);
		test->exit_status = 22;
		return (0);
	}
	return (1);
}

int	check_redirection_operator(t_shell *test, int i)
{
	if (!test || !test->input || i < 0 || !test->input[i])
		return (0);
	if (is_redirection_operatora(test->input[i]))
	{
		if (test->input[i] == '<' || test->input[i] == '>')
		{
			if (!check_same_operator_case(test, i))
				return (0);
			else if (!check_mixed_operator_case(test, i))
				return (0);
		}
	}
	return (1);
}

int	check_redirections(t_shell *test)
{
	int	i;

	if (!test)
		return (0);
	i = 0;
	if (test->dir_count >= 1)
	{
		while (test->input[i])
		{
			if (!check_redirection_operator(test, i))
				return (0);
			i++;
		}
	}
	return (1);
}

int	check_quotes(t_shell *test)
{
	int	i;
	int	s_num_q;
	int	d_num_q;

	if (!test || !test->input)
		return (0);
	i = 0;
	s_num_q = 0;
	d_num_q = 0;
	while (test->input[i])
	{
		if (test->input[i] == '\'')
			s_num_q++;
		if (test->input[i] == '\"')
			d_num_q++;
		i++;
	}
	if (s_num_q % 2 != 0 || d_num_q % 2 != 0)
	{
		return (check_quotes_utils(test));
	}
	return (1);
}

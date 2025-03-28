/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:54:16 by shoaib            #+#    #+#             */
/*   Updated: 2025/03/21 15:11:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_pipe(t_shell *shell)
{
	int	i;
	int	in_single_quotes;
	int	in_double_quotes;

	if (!shell || !shell->input)
		return ;
	i = 0;
	in_double_quotes = 0;
	in_single_quotes = 0;
	shell->count_pipe = 0;
	while (shell->input[i])
	{
		if (shell->input[i] == '"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		else if (shell->input[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		if (shell->input[i] == '|' && !in_double_quotes && !in_single_quotes)
			shell->count_pipe++;
		i++;
	}
}

int	count_max_operate(t_shell *test, int y)
{
	int	count;
	int	i;
	int	command_index;

	if (!test || !test->input_splitted)
		return (0);
	count = 0;
	i = 0;
	command_index = 0;
	while (test->input_splitted[i])
	{
		if (ft_strcmp(test->input_splitted[i], "|") == 0)
			command_index++;
		else if (command_index == y)
		{
			if (ft_strcmp(test->input_splitted[i], "<") == 0
				|| ft_strcmp(test->input_splitted[i], ">") == 0
				|| ft_strcmp(test->input_splitted[i], "<<") == 0
				|| ft_strcmp(test->input_splitted[i], ">>") == 0)
				count++;
		}
		i++;
	}
	return (count);
}

void	allocate_operate_array(t_shell *test)
{
	if (!test)
		return ;
	test->operate = malloc(sizeof(char **) * (test->count_pipe + 2));
	if (!test->operate)
		return ;
}

void	process_input(t_shell *test, int *j, int y)
{
	int	x;

	if (!test || !test->input_splitted)
		return ;
	x = 0;
	while (test->input_splitted[*j] && (ft_strcmp(test->input_splitted[*j],
				"|") != 0))
	{
		if (ft_strcmp(test->input_splitted[*j], "<") == 0
			|| ft_strcmp(test->input_splitted[*j], ">") == 0
			|| ft_strcmp(test->input_splitted[*j], "<<") == 0
			|| ft_strcmp(test->input_splitted[*j], ">>") == 0)
		{
			test->operate[y][x] = test->input_splitted[*j];
			if (!test->operate[y][x])
			{
				printf("Memory allocation failed for operate\n");
				return ;
			}
			(*test).operate_count++;
			x++;
		}
		(*j)++;
	}
	test->operate[y][x] = NULL;
}

void	operate(t_shell *test)
{
	int	j;
	int	y;

	if (!test)
		return ;
	j = 0;
	y = 0;
	test->operate_count = 0;
	allocate_operate_array(test);
	while (y < test->count_pipe + 1)
	{
		test->operate[y] = malloc(sizeof(char *) * (count_max_operate(test, y)
					+ 1));
		if (!test->operate[y])
			return ;
		process_input(test, &j, y);
		if (test->input_splitted[j])
			j++;
		y++;
	}
	test->operate[y] = NULL;
}

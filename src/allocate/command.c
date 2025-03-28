/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:54:09 by shoaib            #+#    #+#             */
/*   Updated: 2025/03/21 15:10:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if(t_shell *test, int i)
{
	if (!test || !test->input_splitted || !test->input_splitted[i])
		return (0);
	if (i > 0 && !test->input_splitted[i - 1])
		return (0);
	return (ft_strcmp(test->input_splitted[i], "<<") != 0
		&& ft_strcmp(test->input_splitted[i], "<") != 0
		&& ft_strcmp(test->input_splitted[i], ">>") != 0
		&& ft_strcmp(test->input_splitted[i], ">") != 0
		&& ft_strcmp(test->input_splitted[i], "|") != 0 && (i == 0
			|| (ft_strcmp(test->input_splitted[i - 1], "<<") != 0
				&& ft_strcmp(test->input_splitted[i - 1], "<") != 0
				&& ft_strcmp(test->input_splitted[i - 1], ">>") != 0
				&& ft_strcmp(test->input_splitted[i - 1], ">") != 0)));
}

void	process_commands_loop(t_shell *test, int *i, int *j)
{
	int	pipe;

	if (!test || !test->input_splitted || !test->command || !i || !j)
		return ;
	pipe = 0;
	while (test->input_splitted[*i])
	{
		if (ft_strcmp(test->input_splitted[*i], "|") == 0)
			pipe += 1;
		if (check_if(test, *i))
		{
			store_command(test, j, *i);
			if (pipe > 0)
				pipe -= 1;
		}
		else if (pipe == 2 || (pipe == 1 && test->input_splitted[*i
					+ 1] == NULL))
		{
			test->command[(*j)++] = NULL;
			pipe -= 1;
		}
		(*i)++;
	}
}

void	process_commands(t_shell *test)
{
	int	i;
	int	j;

	if (!test || !test->input_splitted || !test->command)
		return ;
	i = 0;
	j = 0;
	if (handle_pipes(test, &i, &j) == -1)
		return ;
	process_commands_loop(test, &i, &j);
	test->command[j] = NULL;
}

void	command_count(t_shell *test)
{
	int	x;

	if (!test)
		return ;
	x = count_max_commands(test);
	if (x > test->count_pipe)
		test->command = malloc(sizeof(char **) * (x + 1));
	else
		test->command = malloc(sizeof(char **) * (test->count_pipe + 2));
	if (!test->command)
	{
		printf("Memory allocation failed for command array\n");
		return ;
	}
	process_commands(test);
}

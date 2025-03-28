/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:54:13 by shoaib            #+#    #+#             */
/*   Updated: 2025/03/22 03:06:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_max_dir(t_shell *test, int y)
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

void	store_redirect(t_shell *test, int *j, int y, int *x)
{
	if (!test || !test->input_splitted || !test->dir || !j || !x)
		return ;
	if (test->input_splitted[*j + 1] && test->input_splitted[*j + 1][0] != '\0')
	{
		test->dir[y][*x] = test->input_splitted[*j + 1];
		test->dir_count++;
		(*x)++;
		(*j)++;
	}
	else
		test->dir[y][*x] = NULL;
}

void	process_dir_input(t_shell *test, int *j, int y)
{
	int	x;

	if (!test || !test->input_splitted || !test->dir || !j)
		return ;
	x = 0;
	while (test->input_splitted[*j] && (ft_strcmp(test->input_splitted[*j],
				"|") != 0))
	{
		if ((ft_strcmp(test->input_splitted[*j], "<") == 0
				|| ft_strcmp(test->input_splitted[*j], ">") == 0
				|| ft_strcmp(test->input_splitted[*j], "<<") == 0
				|| ft_strcmp(test->input_splitted[*j], ">>") == 0)
			&& ft_strcmp(test->input_splitted[*j], "|") != 0)
		{
			store_redirect(test, j, y, &x);
		}
		(*j)++;
	}
	test->dir[y][x] = NULL;
	if (test->input_splitted[*j])
		(*j)++;
}

void	dir(t_shell *test)
{
	int	j;
	int	y;

	if (!test || !test->input_splitted)
		return ;
	j = 0;
	y = 0;
	test->dir_count = 0;
	test->dir = malloc(sizeof(char **) * (test->count_pipe + 2));
	if (!test->dir)
		return ;
	while (y < test->count_pipe + 1)
	{
		test->dir[y] = malloc(sizeof(char *) * (count_max_dir(test, y) + 1));
		if (!test->dir[y])
			return ;
		process_dir_input(test, &j, y);
		y++;
	}
	test->dir[y] = NULL;
}

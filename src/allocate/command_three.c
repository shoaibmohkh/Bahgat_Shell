/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_three.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 22:23:29 by marvin            #+#    #+#             */
/*   Updated: 2025/03/22 07:57:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_max_commands(t_shell *test)
{
	int	count;
	int	i;

	if (!test->input_splitted || !test)
		return (0);
	count = 0;
	i = 0;
	while (test->input_splitted[i])
	{
		if (ft_strcmp(test->input_splitted[i], "<<") != 0
			&& ft_strcmp(test->input_splitted[i], "<") != 0
			&& ft_strcmp(test->input_splitted[i], ">>") != 0
			&& ft_strcmp(test->input_splitted[i], ">") != 0
			&& ft_strcmp(test->input_splitted[i], "|") != 0 && (i == 0
				|| (ft_strcmp(test->input_splitted[i - 1], "<<") != 0
					&& ft_strcmp(test->input_splitted[i - 1], "<") != 0
					&& ft_strcmp(test->input_splitted[i - 1], ">>") != 0
					&& ft_strcmp(test->input_splitted[i - 1], ">") != 0)))
		{
			count++;
			test->command_count++;
		}
		i++;
	}
	return (count);
}

void	store_command(t_shell *test, int *j, int i)
{
	if (i < 0 || !test || !test->split_the_split)
		return ;
	test->command[*j] = test->split_the_split[i];
	(*j)++;
}

int	ch(char **t, int h)
{
	if (!t || h < 0)
		return (0);
	return (ft_strcmp(t[h], "<<") != 0
		&& ft_strcmp(t[h], "<") != 0
		&& ft_strcmp(t[h], ">>") != 0
		&& ft_strcmp(t[h], ">") != 0
		&& ft_strcmp(t[h], "|") != 0
		&& (h == 0 || (ft_strcmp(t[h - 1], "<<") != 0
				&& ft_strcmp(t[h - 1], "<") != 0
				&& ft_strcmp(t[h - 1], ">>") != 0
				&& ft_strcmp(t[h - 1], ">") != 0)));
}

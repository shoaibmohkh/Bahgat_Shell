/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 22:12:29 by marvin            #+#    #+#             */
/*   Updated: 2025/03/16 22:12:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_first_pipe(t_shell *test, int *i)
{
	if (!test || !test->input_splitted || !i)
		return ;
	while (ft_strcmp(test->input_splitted[*i], "|") != 0
		&& test->input_splitted[*i])
		(*i)++;
}

char	**create_temp_array(t_shell *test, int index)
{
	char	**t;
	int		h;

	if (!test || !test->input_splitted || index < 0)
		return (NULL);
	t = malloc(sizeof(char *) * (index + 1));
	if (!t)
		return (NULL);
	h = 0;
	while (h < index)
	{
		t[h] = test->input_splitted[h];
		h++;
	}
	t[h] = NULL;
	return (t);
}

int	check_flagg(char **t)
{
	int	h;
	int	flagg;

	if (!t)
		return (1);
	h = 0;
	flagg = 1;
	while (t[h] != NULL)
	{
		if (ch(t, h))
			flagg = 0;
		h++;
	}
	return (flagg);
}

void	update_commands(t_shell *test, int *j, int *i, int flagg)
{
	if (!test || !test->command || !i || !j)
		return ;
	if (flagg)
		test->command[(*j)++] = NULL;
	else
		*i = 0;
}

int	handle_pipes(t_shell *test, int *i, int *j)
{
	char	**t;
	int		flagg;

	if (!test || !i || !j || !test->input_splitted)
		return (-1);
	*i = 0;
	if (test->count_pipe != 0)
	{
		find_first_pipe(test, i);
		t = create_temp_array(test, *i);
		if (!t)
			return (-1);
		flagg = check_flagg(t);
		update_commands(test, j, i, flagg);
		free(t);
	}
	return (0);
}

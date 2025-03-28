/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:34:53 by sal-kawa          #+#    #+#             */
/*   Updated: 2025/03/22 03:12:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_echo_arguments(t_shell *string, int i, int start)
{
	int	j;

	while (string->command[i][start])
	{
		j = 0;
		while (string->command[i][start][j])
		{
			write(1, &string->command[i][start][j], 1);
			j++;
		}
		if (string->command[i][start + 1])
			write(1, " ", 1);
		start++;
	}
}

int	handle_special_cases(t_shell *string, int i)
{
	char	*home;

	if (string->command[i][1] && ft_strcmp(string->command[i][1], "~") == 0
		&& string->command[i][2] == NULL)
	{
		home = get_env_value(string, "HOME");
		if (home)
			printf("%s\n", home);
		else
			string->exit_status = 1;
		return (1);
	}
	if (!string->command[i][1])
	{
		write(1, "\n", 1);
		string->exit_status = 0;
		return (1);
	}
	return (0);
}

int	check_char_newline(char *flag)
{
	int	j;

	j = 1;
	while (flag[j])
	{
		if (flag[j] != 'n')
			return (0);
		j++;
	}
	return (1);
}

void	check_echo_flags(t_shell *str, int i, int *idx, int *flag)
{
	while (str->command[i][*idx] && str->command[i][*idx][0] == '-'
		&& str->command[i][*idx][1])
	{
		if (check_char_newline(str->command[i][*idx]))
		{
			*flag = 1;
			(*idx)++;
		}
		else
			break ;
	}
}

void	ft_echo(t_shell *string, int i)
{
	int		arg_index;
	int		flag_no_newline;

	arg_index = 1;
	flag_no_newline = 0;
	if (handle_special_cases(string, i))
		return ;
	check_echo_flags(string, i, &arg_index, &flag_no_newline);
	print_echo_arguments(string, i, arg_index);
	if (!flag_no_newline)
		write(1, "\n", 1);
	string->exit_status = 0;
}

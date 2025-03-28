/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-kawa <sal-kawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:47:55 by sal-kawa          #+#    #+#             */
/*   Updated: 2025/03/13 05:18:13 by sal-kawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (1);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && str[i] != ' ')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_exit_arguments(t_shell *shell, int i)
{
	long long	val;

	if (!shell->command[i][1])
	{
		shell->exit_status = 0;
		return (1);
	}
	if (!is_numeric(shell->command[i][1]))
	{
		print_error(shell->name_program, shell->command[i][1],
			"numeric argument required");
		shell->exit_status = 2;
		return (1);
	}
	val = ft_atoi(shell->command[i][1]);
	if (val == LLONG_MAX || (val == LLONG_MIN && ft_strcmp(shell->command[i][1],
			"-9223372036854775808") != 0))
	{
		print_error(shell->name_program, shell->command[i][1],
			"numeric argument required");
		shell->exit_status = 2;
		return (1);
	}
	return (0);
}

int	ft_exit(t_shell *shell, int i)
{
	long	exit_int;

	if (shell->count_pipe == 0)
		printf("exit\n");
	if (check_exit_arguments(shell, i))
		return (1);
	if (shell->command[i][2])
	{
		print_error(shell->name_program, NULL, "too many arguments");
		shell->exit_status = 1;
		return (0);
	}
	exit_int = ft_atoi(shell->command[i][1]);
	if (exit_int > 255)
	{
		shell->exit_status = exit_int % 256;
		return (1);
	}
	if (exit_int < 0)
	{
		shell->exit_status = (exit_int % 256 + 256) % 256;
		return (1);
	}
	shell->exit_status = exit_int;
	return (1);
}

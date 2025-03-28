/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 07:18:39 by marvin            #+#    #+#             */
/*   Updated: 2025/03/12 07:30:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	e_exit(t_shell *shell, int i)
{
	shell->exit_status = i;
	exit(i);
}

void	print_error(char *program, char *arg, char *msg)
{
	if (program != NULL)
	{
		write(2, program, ft_strlen(program));
		write(2, ": ", 2);
	}
	if (arg != NULL)
	{
		write(2, arg, ft_strlen(arg));
		write(2, ": ", 2);
	}
	if (msg != NULL)
	{
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
	}
}

void	free_dir_operate(t_shell *shell)
{
	int	i;

	if (shell->dir)
	{
		i = 0;
		while (shell->dir && shell->dir[i])
			free(shell->dir[i++]);
		if (shell->dir)
			free(shell->dir);
	}
	if (shell->operate)
	{
		i = 0;
		while (shell->operate && shell->operate[i])
			free(shell->operate[i++]);
		if (shell->operate)
			free(shell->operate);
	}
}

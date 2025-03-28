/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:35:01 by sal-kawa          #+#    #+#             */
/*   Updated: 2025/03/22 05:54:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_shell *shell)
{
	char	path[1024];
	int		i;

	if (getcwd(path, sizeof(path)))
	{
		i = 0;
		while (path[i])
		{
			write(1, &path[i], 1);
			i++;
		}
		write(1, "\n", 1);
		shell->exit_status = 0;
	}
	else
	{
		print_error("minishell", "pwd", "Failed to retrieve current directory");
		shell->exit_status = 1;
	}
}

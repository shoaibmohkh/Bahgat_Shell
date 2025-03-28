/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:24:15 by ikhalil           #+#    #+#             */
/*   Updated: 2025/03/12 07:23:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_shell_signal;

void	handle_signals(int sig)
{
	if (sig == SIGINT)
	{
		g_shell_signal = SIGINT;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	change_sigint(int sig)
{
	(void)sig;
	g_shell_signal = SIGINT;
	close(STDIN_FILENO);
}

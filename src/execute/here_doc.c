/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-kawa <sal-kawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:00:58 by sal-kawa          #+#    #+#             */
/*   Updated: 2025/03/19 21:28:20 by sal-kawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc_read_loop(char *delimiter, t_here_doc_data *data, t_shell *test)
{
	char	*line;

	while (g_shell_signal != SIGINT)
	{
		line = readline("> ");
		if (process_here_doc_line(delimiter, data, test, line))
			break ;
	}
	return (1);
}

int	here_doc_finalize(t_here_doc_data *data, int *in_fd)
{
	restore_stdin(data->saved_stdin);
	signal(SIGINT, handle_signals);
	if (g_shell_signal == SIGINT)
	{
		free(data->accumulator);
		close(data->pipe_fd[1]);
		close(data->pipe_fd[0]);
		*in_fd = STDIN_FILENO;
		return (0);
	}
	write(data->pipe_fd[1], data->accumulator, ft_strlen(data->accumulator));
	free(data->accumulator);
	close(data->pipe_fd[1]);
	*in_fd = data->pipe_fd[0];
	return (1);
}

int	handle_here_doc(char *delimiter, int *in_fd, t_shell *test)
{
	t_here_doc_data	data;

	if (*in_fd != STDIN_FILENO)
	{
		close(*in_fd);
		*in_fd = STDIN_FILENO;
	}
	if (!here_doc_setup(&data))
		return (0);
	signal(SIGINT, change_sigint);
	g_shell_signal = 0;
	here_doc_read_loop(delimiter, &data, test);
	return (here_doc_finalize(&data, in_fd));
}

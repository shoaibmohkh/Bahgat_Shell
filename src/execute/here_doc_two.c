/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-kawa <sal-kawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:02:06 by sal-kawa          #+#    #+#             */
/*   Updated: 2025/03/13 06:37:08 by sal-kawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_here_doc_util(char **accumulator, char *line, t_shell *test)
{
	char	*temp;

	temp = *accumulator;
	*accumulator = ft_strjoin(*accumulator, line);
	free(temp);
	free(line);
	if (!*accumulator)
		return (1);
	temp = *accumulator;
	*accumulator = ft_strjoin(*accumulator, "\n");
	free(temp);
	if (!*accumulator)
		return (1);
	if (g_shell_signal == SIGINT)
	{
		test->exit_status = 130;
		test->flag_here = 1;
		return (1);
	}
	return (0);
}

void	restore_stdin(int saved_stdin)
{
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
}

int	here_doc_setup(t_here_doc_data *data)
{
	if (pipe(data->pipe_fd) == -1)
	{
		perror("pipe");
		return (0);
	}
	data->saved_stdin = dup(STDIN_FILENO);
	data->accumulator = ft_strdup("");
	if (!data->accumulator)
	{
		close(data->pipe_fd[0]);
		close(data->pipe_fd[1]);
		return (0);
	}
	return (1);
}

int	process_here_doc_line(char *delimiter, t_here_doc_data *data, t_shell *test,
		char *line)
{
	if (g_shell_signal == SIGINT)
	{
		printf(">\n");
		test->exit_status = 130;
		test->flag_here = 1;
		free(line);
		return (1);
	}
	if (!line)
	{
		print_error(test->name_program, "warning",
			"here-document at line 1 delimited by end-of-file (wanted `end')");
		test->exit_status = 0;
		return (1);
	}
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (1);
	}
	if (handle_here_doc_util(&(data->accumulator), line, test))
		return (1);
	return (0);
}

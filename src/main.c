/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:46:28 by sal-kawa          #+#    #+#             */
/*   Updated: 2025/03/28 14:13:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop_shell(t_shell *test)
{
	int	ret_input;

	while (1)
	{
		g_shell_signal = 0;
		signal(SIGINT, handle_signals);
		signal(SIGQUIT, SIG_IGN);
		ret_input = input_phase(test);
		if (ret_input == 0)
			break ;
		if (ret_input == 2)
			continue ;
		signal(SIGINT, SIG_IGN);
		ret_input = command_phase(test);
		if (ret_input == 2)
			continue ;
	}
}

int	main(int argc, char **argv)
{
	t_shell	test;
	int		fd;
	char	buffer[1024];
	ssize_t	bytes_read;

	fd = open("ascii_image.txt", O_RDONLY);
	while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
		write(STDOUT_FILENO, buffer, bytes_read);
	close(fd);
	write(1, "\n", 1);
	init_shell(&test, argc, argv);
	loop_shell(&test);
	rl_clear_history();
	free_shell(&test, 1, 1);
	e_exit(&test, 0);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 07:39:20 by marvin            #+#    #+#             */
/*   Updated: 2025/03/28 14:36:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell *test, int argc, char **argv)
{
	if (!test || !argv)
		return ;
	(void)argc;
	ft_bzero(test, sizeof(t_shell));
	ft_env_init(test);
	re_shlvl(test);
	if (argv[0])
		test->name_program = argv[0];
}

int	handle_input(t_shell *test)
{
	char prompt[1200];
	char cwd[1024];

	if (!test)
		return (0);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd() error");
		return 1;
	}
	snprintf(prompt, sizeof(prompt),
		"\033[31m\033[1mBahgat_Shell:\033[38;5;22m\033[1m%s\033[31m\033[1m> \033[0m"
	, cwd);
	test->input = readline(prompt);
	if (!test->input)
	{
		write(2, "exit\n", 5);
		return (0);
	}
	if (!test->input[0])
	{
		free_shell(test, 0, 1);
		return (2);
	}
	add_history(test->input);
	if (g_shell_signal == SIGINT)
		test->exit_status = 130;
	return (1);
}

int	split_input(t_shell *test)
{
	if (!test)
		return (0);
	test->input_splitted = ft_split(test->input, test);
	if (!test->input_splitted || !test->input_splitted[0])
	{
		free_shell(test, 0, 1);
		return (0);
	}
	test->split_the_split = split_commands(test->input_splitted);
	if (!test->split_the_split || !test->split_the_split[0])
	{
		free_shell(test, 0, 1);
		return (0);
	}
	return (1);
}

void	expand_all_tokens(t_shell *test)
{
	int	i;

	if (!test)
		return ;
	i = 0;
	while (test->split_the_split[i])
	{
		if (test->split_the_split[i][0] == NULL)
		{
			i++;
			break ;
		}
		if (ft_strcmp(test->split_the_split[i][0], "export") == 0)
		{
			i++;
			continue ;
		}
		expand_tokens_in_row(&(test->split_the_split[i]), test);
		i++;
	}
}

int	check_same_operator_case(t_shell *test, int i)
{
	if (!test || !test->input)
		return (0);
	if (test->input[i + 1] == test->input[i])
	{
		if (test->input[i + 2] == test->input[i] || (test->input[i + 1] == '>'
				&& test->input[i] == '<') || (test->input[i + 1] == '<'
				&& test->input[i] == '>'))
		{
			printf("%s: syntax error near unexpected token '%c%c'\n",
				test->name_program,
				test->input[i],
				test->input[i + 1]);
			free_shell(test, 0, 1);
			test->exit_status = 22;
			return (0);
		}
	}
	return (1);
}

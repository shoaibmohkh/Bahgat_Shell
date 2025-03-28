/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:32:59 by sal-kawa          #+#    #+#             */
/*   Updated: 2025/03/22 08:14:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_env_error_cases(t_shell *test, char **argv)
{
	if (argv[1][ft_strlen(argv[1]) - 1] == '/')
		handle_env_error_slash(test, argv);
	else
	{
		print_error(test->name_program, argv[1], "No such file or directory");
		test->exit_status = 127;
	}
}

void	ft_env(t_shell *test, int i)
{
	int		x;
	char	**argv;

	if (!test || !test->command || !(test->command[i]))
		return ;
	argv = test->command[i];
	if (argv[1] != NULL)
	{
		handle_env_error_cases(test, argv);
		return ;
	}
	x = 0;
	while (test->env[x])
	{
		write(1, test->env[x], ft_strlen(test->env[x]));
		write(1, "\n", 1);
		x++;
	}
	test->exit_status = 0;
}

char	*get_env_value(t_shell *shell, char *key)
{
	int	i;
	int	len;

	if (!shell || !shell->env || !key)
		return (NULL);
	i = 0;
	len = ft_strlen(key);
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], key, len) == 0
			&& shell->env[i][len] == '=')
			return (shell->env[i] + len + 1);
		i++;
	}
	return (NULL);
}

void	ft_env_copy(t_shell *test, char **environ, int i)
{
	int	j;

	if (!test || !environ)
		return ;
	while (environ[i])
	{
		test->env[i] = malloc((ft_strlen(environ[i]) + 1) * sizeof(char));
		if (!test->env[i])
		{
			print_error(test->name_program, "malloc",
				"Memory allocation failed");
			test->exit_status = 1;
			return ;
		}
		j = 0;
		while (environ[i][j])
		{
			test->env[i][j] = environ[i][j];
			j++;
		}
		test->env[i][j] = '\0';
		i++;
	}
	test->env[i] = NULL;
}

void	ft_env_init(t_shell *test)
{
	extern char	**environ;
	int			i;

	if (!test)
		return ;
	i = 0;
	while (environ[i])
		i++;
	test->env = malloc((i + 1) * sizeof(char *));
	if (!test->env)
	{
		print_error(test->name_program, "malloc", "Memory allocation failed");
		test->exit_status = 1;
		return ;
	}
	ft_env_copy(test, environ, 0);
	test->env[i] = NULL;
	test->exp = NULL;
}

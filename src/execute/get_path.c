/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:24:17 by sal-kawa          #+#    #+#             */
/*   Updated: 2025/03/22 08:56:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*getpath(t_shell *shell, char **test)
{
	char	*path;
	char	*new_path;
	char	*result;

	if (!test || !test[0])
		return (NULL);
	if (ft_strchr(test[0], '/'))
	{
		if (access(test[0], X_OK) == 0)
			return (ft_strdup(test[0]));
		return (NULL);
	}
	path = get_env_value(shell, "PATH");
	if (!path)
		return (NULL);
	new_path = malloc(sizeof(char) * 1024);
	if (!new_path)
		return (NULL);
	result = find_executable(path, new_path, test[0]);
	if (result)
		return (result);
	free(new_path);
	return (NULL);
}

char	*find_executable(char *path, char *new_path, char *test)
{
	char	*start;
	char	*end;
	int		length;

	start = path;
	end = ft_strchr(path, ':');
	while (end != NULL)
	{
		length = end - start;
		ft_strncpy(new_path, start, length);
		new_path[length] = '\0';
		ft_strcat(new_path, "/");
		ft_strcat(new_path, test);
		if (access(new_path, X_OK) == 0)
			return (new_path);
		path += length + 1;
		start = end + 1;
		end = ft_strchr(path, ':');
	}
	ft_strcpy(new_path, start);
	ft_strcat(new_path, "/");
	ft_strcat(new_path, test);
	if (access(new_path, X_OK) == 0)
		return (new_path);
	return (NULL);
}

void	handle_env_error_slash(t_shell *test, char **argv)
{
	int		dir_check;
	char	*tmp;

	tmp = ft_strdup(argv[1]);
	if (!tmp)
	{
		print_error(test->name_program, "ft_strdup",
			"Memory allocation failed");
		test->exit_status = 1;
		return ;
	}
	tmp[ft_strlen(tmp) - 1] = '\0';
	dir_check = check_dir(tmp);
	if (dir_check == 1 || dir_check == 3)
		print_error(test->name_program, argv[1], "Permission denied");
	else if (dir_check == 2)
		print_error(test->name_program, argv[1], "Not a directory");
	else
		print_error(test->name_program, argv[1],
			"No such file or directory");
	free(tmp);
	test->exit_status = 126;
	if (dir_check == 0)
		test->exit_status = 127;
}

void	setup_pipeline_iteration(t_shell *shell, int i, t_pipe_vars *vars)
{
	vars->in_fd = STDIN_FILENO;
	vars->out_fd = STDOUT_FILENO;
	vars->redir_success = 1;
	if (i > 0 && vars->prev_fd != -1)
	{
		vars->in_fd = vars->prev_fd;
	}
	command_pipeline_redirections(shell, i, vars);
	if (!vars->redir_success && vars->pipe_created)
	{
		close(vars->pipe_fd[0]);
		close(vars->pipe_fd[1]);
		vars->pipe_created = 0;
	}
}

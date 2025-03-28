/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_and_shlvl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:32:53 by sal-kawa          #+#    #+#             */
/*   Updated: 2025/03/22 08:01:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	build_and_export_pwd(t_shell *shell, char *path, char *pwd, char *key)
{
	char	*export[3];

	if (!shell || !path || !pwd || !key)
		return ;
	ft_strcpy(pwd, key);
	ft_strcat(pwd, path);
	export[0] = "export";
	export[1] = pwd;
	export[2] = NULL;
	ft_export(shell, export);
}

void	get_old_pwd(t_shell *test)
{
	char	path[1024];
	char	old_pwd[1024];
	char	*pwd_back;

	if (!test)
		return ;
	if (getcwd(path, sizeof(path)) == NULL)
	{
		pwd_back = get_env_value(test, "PWD");
		if (pwd_back == NULL)
		{
			print_error(test->name_program, NULL,
				"getcwd error: No 'PWD' environment variable found");
			test->exit_status = 1;
			return ;
		}
		ft_strncpy(path, pwd_back, sizeof(path) - 1);
		path[sizeof(path) - 1] = '\0';
	}
	build_and_export_pwd(test, path, old_pwd, "OLDPWD=");
}

void	update_pwd(t_shell *shell)
{
	char	path[1024];
	char	pwd[1024];

	if (!shell)
		return ;
	if (getcwd(path, sizeof(path)) == NULL)
	{
		print_error(shell->name_program, NULL, "getcwd error");
		shell->exit_status = 1;
		return ;
	}
	build_and_export_pwd(shell, path, pwd, "PWD=");
}

void	create_shlvl_entry(t_shell *shell, int level)
{
	char	*new_shlvl;
	char	shlvl_with_prefix[1024];

	if (!shell)
		return ;
	new_shlvl = ft_itoa(level);
	if (!new_shlvl)
	{
		print_error(shell->name_program, NULL,
			"Memory allocation failed for SHLVL");
		shell->exit_status = 1;
		return ;
	}
	build_and_export_pwd(shell, new_shlvl, shlvl_with_prefix, "SHLVL=");
	free(new_shlvl);
}

void	re_shlvl(t_shell *shell)
{
	int		level;
	char	*shlvl;

	if (!shell)
		return ;
	shlvl = get_env_value(shell, "SHLVL");
	if (!shlvl || !is_numeric(shlvl))
		level = 1;
	else
	{
		level = ft_atoi(shlvl) + 1;
		if (level < 0)
			level = 0;
		else if (level >= 1000)
		{
			print_error(shell->name_program, "SHLVL",
				"warning: shell level (1000) too high, resetting to 1");
			level = 1;
		}
	}
	create_shlvl_entry(shell, level);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 06:29:40 by marvin            #+#    #+#             */
/*   Updated: 2025/03/21 04:46:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_arg(t_shell *shell, char *arg,
				int *valid_args, int *error_flag)
{
	char	*local_arg;
	char	*inv;

	local_arg = expand_arg(shell, arg, error_flag);
	if (!local_arg)
		return ;
	if (!is_valid_identifier(local_arg))
	{
		inv = get_invalid_identifier(local_arg);
		print_error("export", inv, "not a valid identifier");
		shell->exit_status = 1;
		*error_flag = 1;
		free(inv);
		free(local_arg);
		return ;
	}
	(*valid_args)++;
	if (ft_strchr(local_arg, '=') == NULL)
	{
		add_to_export(shell, local_arg);
		free(local_arg);
		return ;
	}
	process_arg_with_equal(shell, local_arg, error_flag);
}

void	ft_export(t_shell *shell, char **args)
{
	int	valid_args;
	int	error_flag;
	int	i;

	valid_args = 0;
	error_flag = 0;
	if (!args[1])
	{
		print_export_list(shell);
		return ;
	}
	i = 1;
	while (args[i])
	{
		process_arg(shell, args[i], &valid_args, &error_flag);
		i++;
	}
	if (valid_args == 0 && error_flag == 0)
		print_export_list(shell);
}

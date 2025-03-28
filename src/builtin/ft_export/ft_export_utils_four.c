/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils_four.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 06:47:24 by marvin            #+#    #+#             */
/*   Updated: 2025/03/12 06:47:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_arg_with_equal(t_shell *shell, char *arg, int *error_flag)
{
	char	*arg_exp;
	char	*temp;

	arg_exp = expander(arg, shell);
	if (!arg_exp || arg_exp[0] == '=')
	{
		if (arg_exp)
			temp = arg_exp;
		else
			temp = "";
		print_error("export", temp, "not a valid identifier");
		shell->exit_status = 1;
		*error_flag = 1;
		if (arg_exp)
			free(arg_exp);
		return (NULL);
	}
	return (arg_exp);
}

char	*expand_arg_no_equal(t_shell *shell, char *arg)
{
	char	*arg_exp;

	arg_exp = expander(arg, shell);
	if (!arg_exp || arg_exp[0] == '\0')
	{
		if (arg_exp)
			free(arg_exp);
		return (NULL);
	}
	return (arg_exp);
}

char	*expand_arg(t_shell *shell, char *arg, int *error_flag)
{
	char	*args;
	char	*expand_args_with_equal;
	char	*expand_args_no_equal;

	if (arg[0] == '$')
	{
		if (ft_strchr(arg, '='))
		{
			expand_args_with_equal = expand_arg_with_equal(shell, arg,
					error_flag);
			return (expand_args_with_equal);
		}
		expand_args_no_equal = expand_arg_no_equal(shell, arg);
		return (expand_args_no_equal);
	}
	args = ft_strdup(arg);
	if (!args)
		handle_malloc_error();
	return (args);
}

char	*process_dollar_assignment(t_shell *shell, char *local_arg,
					int *error_flag)
{
	char	*eq;
	char	*exp_val;
	char	*left;
	char	*temp;
	char	*new_var;

	eq = ft_strchr(local_arg, '=');
	exp_val = expander(eq + 1, shell);
	if (!exp_val || exp_val[0] == '=')
	{
		print_error("export", "=", "not a valid identifier");
		shell->exit_status = 1;
		*error_flag = 1;
		if (exp_val)
			free(exp_val);
		return (NULL);
	}
	left = get_name_from_env(local_arg);
	temp = ft_strjoin(left, "=");
	new_var = ft_strjoin(temp, exp_val);
	free(left);
	free(temp);
	free(exp_val);
	return (new_var);
}

void	process_arg_with_equal(t_shell *shell,
				char *local_arg, int *error_flag)
{
	char	*eq;
	char	*new_var;
	char	*var_name;

	eq = ft_strchr(local_arg, '=');
	new_var = local_arg;
	if (ft_strchr(eq, '$'))
	{
		new_var = process_dollar_assignment(shell, local_arg, error_flag);
		if (!new_var)
		{
			free(local_arg);
			return ;
		}
	}
	var_name = get_name_from_env(new_var);
	update_env_var(shell, var_name, new_var);
	remove_from_export(shell, var_name);
	free(var_name);
	if (new_var != local_arg)
		free(new_var);
	free(local_arg);
}

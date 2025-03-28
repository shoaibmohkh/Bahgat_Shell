/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_dollar_sign.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:20:48 by ikhalil           #+#    #+#             */
/*   Updated: 2025/03/15 01:58:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_exit_status(char *s, t_shell *shell, t_exp *exp)
{
	char	*status_str;
	char	*tmp;

	status_str = ft_itoa(shell->exit_status);
	if (!status_str)
		return (NULL);
	if (status_str)
	{
		tmp = status_str;
		while (*tmp)
		{
			*(exp->out) = *tmp;
			exp->out++;
			tmp++;
		}
		free(status_str);
	}
	return (s + 1);
}

static char	*handle_shell_name(char *s, t_exp *exp, t_shell *shell)
{
	char	*name;

	name = shell->name_program;
	while (*name)
	{
		*(exp->out) = *name;
		exp->out++;
		name++;
	}
	return (s + 1);
}

static char	*handle_digit(char *s, t_exp *exp)
{
	int	i;
	int	j;

	i = 0;
	while (s[i] && ft_isdigit(s[i]))
		i++;
	if (i == 1)
		return (s + 1);
	else
	{
		j = 1;
		while (j < i)
		{
			*(exp->out) = s[j];
			exp->out++;
			j++;
		}
		return (s + i);
	}
}

static char	*handle_variable(char *s, t_shell *shell, t_exp *exp)
{
	char	var[2048];
	int		i;
	int		j;
	char	*value;

	i = 0;
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_') && i < 127)
	{
		var[i] = s[i];
		i++;
	}
	var[i] = '\0';
	s += i;
	value = get_env_value(shell, var);
	if (!value)
		return (s);
	j = 0;
	while (value[j])
	{
		*(exp->out) = value[j];
		exp->out++;
		j++;
	}
	return (s);
}

char	*deal_with_dollar(char *s, t_shell *shell, t_exp *exp)
{
	s++;
	if (*s == '?')
		return (handle_exit_status(s, shell, exp));
	if (*s == '0')
		return (handle_shell_name(s, exp, shell));
	if (ft_isdigit(*s))
		return (handle_digit(s, exp));
	if (*s == '\0' || (ft_isalpha(*s) == 0 && *s != '_'))
	{
		*(exp->out) = '$';
		exp->out++;
		return (s);
	}
	return (handle_variable(s, shell, exp));
}

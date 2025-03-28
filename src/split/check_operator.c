/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:50:02 by shoaib            #+#    #+#             */
/*   Updated: 2025/03/15 06:39:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	type_of_ope(const char *op)
{
	if (op == NULL)
		return (0);
	return (ft_strcmp(op, ">") == 0 || ft_strcmp(op, ">>") == 0 || ft_strcmp(op,
			"<") == 0 || ft_strcmp(op, "<<") == 0);
}

void	ft_trim(char *str, char **start, char **end)
{
	char	*last;

	while (ft_isspace((unsigned char)*str))
		str++;
	*start = str;
	if (*str == '\0')
	{
		*end = str;
		return ;
	}
	last = str + ft_strlen(str) - 1;
	while (last >= str && ft_isspace((unsigned char)*last))
		last--;
	*end = last + 1;
}

int	is_operator(const char *s, int *op_len)
{
	if (s[0] == '>' && s[1] == '>')
	{
		*op_len = 2;
		return (1);
	}
	else if (s[0] == '<' && s[1] == '<')
	{
		*op_len = 2;
		return (1);
	}
	else if (s[0] == '<' || s[0] == '>' || s[0] == '|')
	{
		*op_len = 1;
		return (1);
	}
	*op_len = 0;
	return (0);
}

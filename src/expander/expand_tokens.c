/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 02:03:58 by marvin            #+#    #+#             */
/*   Updated: 2025/03/16 21:39:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*deal_with_char(char **s, t_shell *shell, t_exp *exp)
{
	if (**s == '$')
		*s = deal_with_dollar(*s, shell, exp);
	else
	{
		*(exp->out) = **s;
		exp->out++;
		(*s)++;
	}
	return (*s);
}

char	*deal_with_double_quote(char *s, t_shell *shell, t_exp *exp)
{
	s++;
	while (*s && *s != '\"')
	{
		s = deal_with_char(&s, shell, exp);
	}
	if (*s == '\"')
		s++;
	return (s);
}

char	*check_type_of_token(char *s, t_shell *shell, t_exp *exp)
{
	while (*s)
	{
		if (*s == '\'')
			s = deal_with_signal_quote(s, exp);
		else if (*s == '\"')
			s = deal_with_double_quote(s, shell, exp);
		else
			s = deal_with_un_quotetd(s, shell, exp);
	}
	return (s);
}

char	*expander(char *token, t_shell *shell)
{
	t_exp	exp;
	char	*s;

	if (!expander_init(token, shell, &exp, &s))
		return (NULL);
	return (expander_finalize(token, &exp));
}

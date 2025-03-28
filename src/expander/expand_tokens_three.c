/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens_three.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 00:35:15 by marvin            #+#    #+#             */
/*   Updated: 2025/03/12 00:35:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_dollar(char *s, t_shell *shell, t_exp *exp)
{
	char	*start_out;
	char	*temp;
	char	*trimmed;
	int		len;
	int		trimmed_len;

	start_out = exp->out;
	s = deal_with_dollar(s, shell, exp);
	len = exp->out - start_out;
	if (len > 0)
	{
		temp = ft_strndup(start_out, len);
		if (!temp)
			handle_malloc_error();
		trimmed = delete_spaces(temp);
		trimmed_len = (int)ft_strlen(trimmed);
		ft_memcpy(start_out, trimmed, (size_t)trimmed_len);
		exp->out = start_out + trimmed_len;
		free(temp);
		free(trimmed);
	}
	return (s);
}

char	*deal_with_un_quotetd(char *s, t_shell *shell, t_exp *exp)
{
	while (*s && *s != '\"' && *s != '\'')
	{
		if (*s == '$')
			s = handle_dollar(s, shell, exp);
		else
		{
			*(exp->out) = *s;
			exp->out++;
			s++;
		}
	}
	return (s);
}

int	expander_init(char *token, t_shell *shell, t_exp *exp, char **s)
{
	if (!token || !shell)
		return (0);
	exp->res = malloc(10000000);
	if (!exp->res)
		return (0);
	exp->out = exp->res;
	*s = token;
	*s = check_type_of_token(*s, shell, exp);
	if (!(*s))
	{
		free(exp->res);
		return (0);
	}
	*(exp->out) = '\0';
	return (1);
}

char	*expander_finalize(char *token, t_exp *exp)
{
	char	*result;
	char	*final;

	if (!token || !exp->res)
		return (NULL);
	if (ft_strchr(token, '\'') || ft_strchr(token, '\"'))
	{
		result = ft_strdup(exp->res);
		free(exp->res);
		return (result);
	}
	final = delete_spaces(exp->res);
	free(exp->res);
	if (!final)
		return (NULL);
	if (final[0] == '\0')
	{
		free(final);
		return (ft_strdup(""));
	}
	return (final);
}

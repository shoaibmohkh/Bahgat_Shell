/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 07:08:05 by ikhalil           #+#    #+#             */
/*   Updated: 2025/03/15 01:56:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	calculate_token_length(const char *str)
{
	const char	*p;
	int			in_quote;
	char		quote;

	p = str;
	in_quote = 0;
	quote = '\0';
	while (*p)
	{
		if (!in_quote && ft_isspace((unsigned char)*p))
			break ;
		if (*p == '\'' || *p == '"')
		{
			if (!in_quote)
			{
				in_quote = 1;
				quote = *p;
			}
			else if (*p == quote)
				in_quote = 0;
		}
		p++;
	}
	return (p - str);
}

void	skip_quote_if_needed(const char **p,
							int *in_quote,
							char *quote)
{
	if (**p == '\'' || **p == '"')
	{
		if (!*in_quote)
		{
			*in_quote = 1;
			*quote = **p;
			(*p)++;
		}
		else if (**p == *quote)
		{
			*in_quote = 0;
			(*p)++;
		}
	}
}

void	fill_token_chars(char *token,
						const char *start,
						size_t token_len)
{
	size_t		pos;
	const char	*p;
	int			in_quote;
	char		quote;

	pos = 0;
	p = start;
	in_quote = 0;
	quote = '\0';
	while (p < start + token_len)
	{
		skip_quote_if_needed(&p, &in_quote, &quote);
		if (p < start + token_len && (!(*p == '\'' || *p == '"')))
			token[pos++] = *p++;
	}
	token[pos] = '\0';
}

char	*copy_token_content(const char *start, size_t token_len)
{
	char	*token;

	token = alloc_token(token_len);
	fill_token_chars(token, start, token_len);
	return (token);
}

char	*extract_token_with_quotes(char **s)
{
	const char	*start;
	size_t		token_len;
	char		*p;
	char		*result;

	start = *s;
	token_len = calculate_token_length(start);
	p = (char *)(start + token_len);
	if (token_len >= 2 && (start[0] == '"' || start[0] == '\'')
		&& start[token_len - 1] == start[0])
	{
		result = handle_special_case(start, token_len, s, p);
		if (result)
			return (result);
	}
	result = copy_token_content(start, token_len);
	*s = (char *)(start + token_len);
	return (result);
}

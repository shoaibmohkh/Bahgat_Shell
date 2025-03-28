/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 07:09:50 by ikhalil           #+#    #+#             */
/*   Updated: 2025/03/21 01:51:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_token_with_quotes(char **s)
{
	char	quote;

	while (**s && !ft_isspace((unsigned char)**s))
	{
		if (**s == '\'' || **s == '"')
		{
			quote = **s;
			(*s)++;
			while (**s && **s != quote)
				(*s)++;
			if (**s == quote)
				(*s)++;
		}
		else
			(*s)++;
	}
}

size_t	count_tokens_with_quotes(char *s)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		skip_spaces(&s);
		if (*s)
		{
			count++;
			skip_token_with_quotes(&s);
		}
	}
	return (count);
}

char	**allocate_token_array(size_t count)
{
	char	**tokens;

	tokens = malloc((count + 1) * sizeof(char *));
	if (!tokens)
		handle_malloc_error();
	return (tokens);
}

void	fill_tokens(char **tokens, char *s)
{
	size_t	i;
	char	*token;

	i = 0;
	while (*s)
	{
		skip_spaces(&s);
		if (*s)
		{
			token = extract_token_with_quotes(&s);
			tokens[i++] = token;
		}
	}
	tokens[i] = NULL;
}

char	**ft_split_whitespace(char *s)
{
	size_t	count;
	char	**tokens;

	count = count_tokens_with_quotes(s);
	tokens = allocate_token_array(count);
	fill_tokens(tokens, s);
	return (tokens);
}

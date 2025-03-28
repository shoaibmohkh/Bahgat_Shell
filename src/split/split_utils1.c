/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:51:24 by shoaib            #+#    #+#             */
/*   Updated: 2025/03/21 01:50:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_count_subwords(char *s)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == ' ')
			s++;
		if (*s)
		{
			count++;
			if (*s == '"')
				skip_quoted_input(&s);
			else
				while (*s && *s != ' ')
					s++;
		}
	}
	return (count);
}

char	*alloc_token(size_t len)
{
	char	*token;

	token = malloc(len + 1);
	if (!token)
		handle_malloc_error();
	return (token);
}

char	*handle_special_case(const char *start,
							size_t token_len,
							char **s,
							char *p)
{
	char	*token;
	size_t	i;

	i = 1;
	while (i < token_len - 1)
	{
		if (start[i] == '$')
		{
			token = ft_strndup(start, token_len);
			if (!token)
				handle_malloc_error();
			*s = p;
			return (token);
		}
		i++;
	}
	return (NULL);
}

void	skip_spaces(char **s)
{
	while (**s && ft_isspace((unsigned char)**s))
		(*s)++;
}

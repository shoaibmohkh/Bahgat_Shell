/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_ft_echo_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 06:40:35 by ikhalil           #+#    #+#             */
/*   Updated: 2025/03/15 02:29:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pr_token(char **s, t_token_info *token_info, int *current_group)
{
	const char	*start;
	size_t		len;

	start = NULL;
	if (ft_isspace((unsigned char)(*s)[0]))
	{
		while (**s && ft_isspace((unsigned char)(**s)))
			(*s)++;
		(*current_group)++;
	}
	else if (**s == '\'' || **s == '"')
		quote_token(s, &start);
	else
		unquoted_token(s, &start);
	if (start)
	{
		len = *s - start;
		store_token(token_info, *current_group, (char *)start, len);
	}
}

void	tokenize_loop(char *s, char **tokens, int *groups, int *token_index)
{
	t_token_info	token_info;
	int				current_group;

	token_info.tokens = tokens;
	token_info.groups = groups;
	token_info.index = token_index;
	current_group = 0;
	while (*s && *token_index < 64)
	{
		pr_token(&s, &token_info, &current_group);
	}
	tokens[*token_index] = NULL;
}

void	tok_input(char *s, char **tokens, int *groups, int *token_index)
{
	tokenize_loop(s, tokens, groups, token_index);
}

size_t	calculate_total_length(char **tokens, int start, int count)
{
	size_t	total_len;
	int		j;

	total_len = 0;
	j = start;
	while (j < start + count)
		total_len += ft_strlen(tokens[j++]);
	return (total_len);
}

char	*merge_group_t(char **tokens, int start, int count)
{
	char	*merged;
	size_t	total_len;
	int		j;

	total_len = calculate_total_length(tokens, start, count);
	merged = malloc(total_len + 1);
	if (!merged)
		handle_malloc_error();
	merged[0] = '\0';
	j = start;
	while (j < start + count)
		ft_strcat(merged, tokens[j++]);
	return (merged);
}

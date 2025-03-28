/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_ft_echo_utils1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 06:37:28 by ikhalil           #+#    #+#             */
/*   Updated: 2025/03/22 03:11:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_malloc_error(void)
{
	perror("malloc");
	exit(1);
}

void	init_malloc(char ***tokens, int **groups)
{
	*tokens = malloc(64 * sizeof(char *));
	*groups = malloc(64 * sizeof(int));
	if (!*tokens || !*groups)
		handle_malloc_error();
}

void	store_token(t_token_info *token_info, int group, char *start,
		size_t len)
{
	token_info->tokens[*token_info->index] = ft_strndup(start, len);
	if (!token_info->tokens[*token_info->index])
		handle_malloc_error();
	token_info->groups[*token_info->index] = group;
	(*token_info->index)++;
}

void	quote_token(char **s, const char **start)
{
	char	quote;

	quote = **s;
	*start = *s;
	(*s)++;
	while (**s && **s != quote)
		(*s)++;
	if (**s == quote)
		(*s)++;
}

void	unquoted_token(char **s, const char **start)
{
	*start = *s;
	while (**s && !ft_isspace((unsigned char)**s) && **s != '\'' && **s != '"')
		(*s)++;
}

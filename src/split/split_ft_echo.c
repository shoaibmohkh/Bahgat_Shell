/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_ft_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 06:32:14 by ikhalil           #+#    #+#             */
/*   Updated: 2025/03/21 01:48:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	group_loop(char **tokens, int *groups, int token_count,
		char **final_tokens)
{
	int	i;
	int	j;
	int	grp;
	int	count;
	int	final_index;

	i = 0;
	final_index = 0;
	while (i < token_count)
	{
		grp = groups[i];
		j = i;
		count = 0;
		while (j < token_count && groups[j] == grp)
		{
			count++;
			j++;
		}
		if (count == 1)
			final_tokens[final_index++] = ft_strdup(tokens[i]);
		else
			final_tokens[final_index++] = merge_group_t(tokens, i, count);
		i += count;
	}
	final_tokens[final_index] = NULL;
}

char	**group_tokens(char **tokens, int *groups, int token_count)
{
	char	**final_tokens;

	final_tokens = malloc((token_count + 1) * sizeof(char *));
	if (!final_tokens)
		handle_malloc_error();
	group_loop(tokens, groups, token_count, final_tokens);
	return (final_tokens);
}

char	**ft_split_echo(char *s)
{
	char	**tokens;
	char	**final_tokens;
	int		*groups;
	int		token_index;
	int		i;

	token_index = 0;
	init_malloc(&tokens, &groups);
	tok_input(s, tokens, groups, &token_index);
	final_tokens = group_tokens(tokens, groups, token_index);
	i = 0;
	while (i < token_index)
		free(tokens[i++]);
	free(tokens);
	free(groups);
	return (final_tokens);
}

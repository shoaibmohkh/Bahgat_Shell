/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:54:58 by shoaib            #+#    #+#             */
/*   Updated: 2025/03/21 01:50:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_tok_data(t_tok_data *data, int max_tokens, char **tokens)
{
	data->tokens = tokens;
	data->max_tokens = max_tokens;
	data->cmd_flags = malloc(max_tokens * sizeof(int));
	if (!data->cmd_flags)
		handle_malloc_error();
	data->state.token_count = 0;
	data->state.last_cmd_index = -1;
	data->state.has_command = 0;
	data->state.prev_redir = 0;
}

char	**ft_split(const char *input, t_shell *shell)
{
	int			max_tokens;
	char		**tokens;
	t_tok_data	data;
	int			token_count;

	max_tokens = 100;
	tokens = malloc((max_tokens + 1) * sizeof(char *));
	if (!tokens)
		handle_malloc_error();
	init_tok_data(&data, max_tokens, tokens);
	token_count = tokenize_input(shell, input, &data);
	tokens[token_count] = NULL;
	free(data.cmd_flags);
	return (tokens);
}

void	skip_quoted_input(char **s)
{
	(*s)++;
	while (**s && **s != '"')
		(*s)++;
	if (**s == '"')
		(*s)++;
}

char	***allocate_split(char **s, size_t *count)
{
	char	***final_split;

	*count = 0;
	if (!s)
		return (NULL);
	while (s[*count])
		(*count)++;
	final_split = malloc((*count + 1) * sizeof(char **));
	if (!final_split)
		return (NULL);
	final_split[*count] = NULL;
	return (final_split);
}

char	***split_commands(char **s)
{
	char	***final_split;
	size_t	count;
	size_t	i;

	final_split = allocate_split(s, &count);
	if (!final_split)
		return (NULL);
	i = 0;
	while (i < count)
	{
		if (!ft_strncmp(s[i], "echo", 4) && (s[i][4] == ' ' || s[i][4] == '\0'))
			final_split[i] = ft_split_echo(s[i]);
		else if (!ft_strncmp(s[i], "export", 6) && (s[i][6] == ' '
			|| s[i][6] == '\0'))
			final_split[i] = ft_split_export(s[i]);
		else
			final_split[i] = ft_split_whitespace(s[i]);
		i++;
	}
	return (final_split);
}

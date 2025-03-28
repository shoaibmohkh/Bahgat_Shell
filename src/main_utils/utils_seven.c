/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_seven.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 22:27:58 by sal-kawa          #+#    #+#             */
/*   Updated: 2025/03/22 07:45:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**merge_tokens(char **old_tokens, char **split, int j)
{
	char	**new_tokens;
	int		i;

	if (!old_tokens || !split)
		return (NULL);
	new_tokens = allocate_new_tokens(old_tokens, split);
	if (!new_tokens)
		return (NULL);
	new_tokens = merge_tokens_core(old_tokens, split, j, new_tokens);
	i = 0;
	while (old_tokens[i])
		free(old_tokens[i++]);
	free(old_tokens);
	return (new_tokens);
}

void	merge_expanded_token(char ***tokens_ptr, t_shell *shell, int *j_ptr,
		char **input_splitted_x)
{
	char	***split_the_split_x;
	char	**tokens;

	if (!tokens_ptr || !*tokens_ptr || !input_splitted_x)
		return ;
	(void)shell;
	tokens = *tokens_ptr;
	split_the_split_x = split_commands(input_splitted_x);
	if (!split_the_split_x || !split_the_split_x[0])
	{
		free(tokens[*j_ptr]);
		tokens[*j_ptr] = ft_strdup("");
		free_2d(input_splitted_x);
		free_3d(split_the_split_x);
		(*j_ptr)++;
		return ;
	}
	tokens = merge_tokens(tokens, split_the_split_x[0], *j_ptr);
	if (!tokens)
		return ;
	*j_ptr += count_tokens(split_the_split_x[0]);
	free_2d(input_splitted_x);
	free_3d(split_the_split_x);
	*tokens_ptr = tokens;
}

void	process_token_with_dollar(char ***tokens_ptr,
								t_shell *shell,
								int *j_ptr)
{
	char	**tokens;
	char	*expanded;
	char	**input_splitted_x;

	if (!tokens_ptr || !*tokens_ptr || !j_ptr)
		return ;
	tokens = *tokens_ptr;
	expanded = expander(tokens[*j_ptr], shell);
	if (!expanded)
		return ;
	if (expanded[0] == '\0' || is_only_whitespace(expanded))
	{
		free(expanded);
		free(tokens[*j_ptr]);
		shift_tokens_left(tokens, *j_ptr);
		*j_ptr = 0;
		return ;
	}
	input_splitted_x = ft_split(expanded, shell);
	free(expanded);
	if (!input_splitted_x)
		return ;
	merge_expanded_token(tokens_ptr, shell, j_ptr, input_splitted_x);
}

void	process_token_without_dollar(char **tokens, t_shell *shell, int j)
{
	char	*expanded;

	if (!tokens || !shell || j < 0)
		return ;
	expanded = expander(tokens[j], shell);
	if (!expanded)
		return ;
	free(tokens[j]);
	tokens[j] = expanded;
}

void	expand_tokens_in_row(char ***tokens_ptr, t_shell *shell)
{
	int		j;
	char	**tokens;

	if (!tokens_ptr || !*tokens_ptr || !shell)
		return ;
	j = 0;
	tokens = *tokens_ptr;
	while (tokens[j])
	{
		if (ft_strchr(tokens[j], '$') && !ft_strchr(tokens[j], '\'')
			&& !ft_strchr(tokens[j], '\"'))
		{
			process_token_with_dollar(tokens_ptr, shell, &j);
			tokens = *tokens_ptr;
		}
		else
		{
			process_token_without_dollar(tokens, shell, j);
			j++;
		}
	}
}

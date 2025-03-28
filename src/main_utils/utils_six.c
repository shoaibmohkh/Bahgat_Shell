/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_six.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 22:26:30 by sal-kawa          #+#    #+#             */
/*   Updated: 2025/03/22 07:39:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_tokens(char **arr)
{
	int	count;

	if (!arr)
		return (0);
	count = 0;
	while (arr[count])
		count++;
	return (count);
}

void	shift_tokens_left(char **tokens, int index)
{
	int	k;

	if (!tokens)
		return ;
	k = index;
	while (tokens[k + 1])
	{
		tokens[k] = tokens[k + 1];
		k++;
	}
	tokens[k] = NULL;
}

void	copy_tokens(char **dest, int *dest_index, char **src, t_range range)
{
	int	i;

	if (!dest || !src || range.start < 0 || range.end <= range.start)
		return ;
	i = range.start;
	while (i < range.end)
	{
		dest[*dest_index] = ft_strdup(src[i]);
		if (!dest)
			handle_malloc_error();
		(*dest_index)++;
		i++;
	}
}

char	**allocate_new_tokens(char **old_tokens, char **split)
{
	int		orig_count;
	int		exp_count;
	int		new_size;
	char	**new_tokens;

	if (!old_tokens || !split)
		return (NULL);
	orig_count = count_tokens(old_tokens);
	exp_count = count_tokens(split);
	new_size = orig_count - 1 + exp_count;
	new_tokens = malloc(sizeof(char *) * (new_size + 1));
	if (!new_tokens)
		return (NULL);
	return (new_tokens);
}

char	**merge_tokens_core(char **old_tokens, char **split, int j,
		char **new_tokens)
{
	int	new_index;
	int	exp_count;

	if (!old_tokens || !split || !new_tokens)
		return (NULL);
	new_index = 0;
	copy_tokens(new_tokens, &new_index, old_tokens, (t_range){0, j});
	exp_count = count_tokens(split);
	copy_tokens(new_tokens, &new_index, split, (t_range){0, exp_count});
	copy_tokens(new_tokens, &new_index, old_tokens, (t_range){j + 1,
		count_tokens(old_tokens)});
	new_tokens[new_index] = NULL;
	return (new_tokens);
}

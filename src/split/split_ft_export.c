/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_ft_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 04:00:53 by ikhalil           #+#    #+#             */
/*   Updated: 2025/03/21 01:49:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_command(char **s_ptr)
{
	char	*start;
	char	*cmd;
	char	*s;

	s = *s_ptr;
	while (*s && *s == ' ')
		s++;
	start = s;
	while (*s && !ft_isspace((unsigned char)*s))
		s++;
	*s_ptr = s;
	cmd = ft_strndup(start, s - start);
	if (!cmd)
		handle_malloc_error();
	return (cmd);
}

char	**build_tokens_with_arguments(char *cmd, char **args)
{
	char	**tokens;
	int		count;
	int		i;

	count = 0;
	while (args[count])
		count++;
	tokens = malloc(sizeof(char *) * (count + 2));
	if (!tokens)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	tokens[0] = cmd;
	i = 0;
	while (args[i])
	{
		tokens[i + 1] = args[i];
		i++;
	}
	tokens[i + 1] = NULL;
	return (tokens);
}

char	**build_tokens_with_no_argumnets(char *cmd)
{
	char	**tokens;

	tokens = malloc(sizeof(char *) * 2);
	if (!tokens)
		handle_malloc_error();
	tokens[0] = cmd;
	tokens[1] = NULL;
	return (tokens);
}

char	**build_tokens(char *cmd, char *s)
{
	char	**args;
	char	**tokens;

	while (*s && *s == ' ')
		s++;
	if (*s)
	{
		args = ft_split_whitespace(s);
		tokens = build_tokens_with_arguments(cmd, args);
		free(args);
		return (tokens);
	}
	else
		return (build_tokens_with_no_argumnets(cmd));
}

char	**ft_split_export(char *s)
{
	char	*cmd;
	char	**tokens;

	cmd = extract_command(&s);
	tokens = build_tokens(cmd, s);
	return (tokens);
}

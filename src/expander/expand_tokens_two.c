/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 20:04:34 by sal-kawa          #+#    #+#             */
/*   Updated: 2025/03/16 07:28:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_extra_spaces_helper(char *s, char *new, int *i, int *j)
{
	while (s[*i])
	{
		if (s[*i] != ' ')
			new[(*j)++] = s[(*i)++];
		else
		{
			new[(*j)++] = ' ';
			while (s[*i] == ' ')
				(*i)++;
		}
	}
}

char	*remove_extra_spaces(char *s, char *new)
{
	int	i;
	int	j;
	int	len;
	int	has_leading;
	int	has_trailing;

	i = 0;
	j = 0;
	len = ft_strlen(s);
	has_leading = (len > 0 && s[0] == ' ');
	has_trailing = (len > 0 && s[len - 1] == ' ');
	if (has_leading)
		new[j++] = ' ';
	while (s[i] == ' ')
		i++;
	remove_extra_spaces_helper(s, new, &i, &j);
	if (has_trailing && (j == 0 || new[j - 1] != ' '))
		new[j++] = ' ';
	new[j] = '\0';
	return (new);
}

char	*delete_spaces(char *s)
{
	int		len;
	char	*new;

	len = ft_strlen(s);
	new = malloc(len + 1);
	if (new == NULL)
		return (NULL);
	return (remove_extra_spaces(s, new));
}

int	should_delete_sp(char *token)
{
	int		start;
	int		end;
	int		len;
	char	c;

	if (token == NULL || token[0] == '\0')
		return (1);
	c = token[0];
	if (c != '\"' && c != '\'')
		return (1);
	start = 0;
	while (token[start] && token[start] == c)
		start++;
	len = ft_strlen(token);
	end = len - 1;
	while (end >= 0 && token[end] == c)
		end--;
	if ((start % 2) == 1 && (((len - 1) - end) % 2) == 1)
		return (0);
	return (1);
}

char	*deal_with_signal_quote(char *s, t_exp *exp)
{
	s++;
	while (*s && *s != '\'')
	{
		*(exp->out) = *s;
		exp->out++;
		s++;
	}
	if (*s == '\'')
		s++;
	return (s);
}

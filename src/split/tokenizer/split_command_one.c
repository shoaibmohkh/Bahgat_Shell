/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command_one.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:17:57 by shoaib            #+#    #+#             */
/*   Updated: 2025/03/15 06:41:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenize_input(t_shell *g_shell, const char *input, t_tok_data *data)
{
	const char	*p;
	int			op_len;

	p = input;
	op_len = 0;
	while (*p && data->state.token_count < data->max_tokens)
	{
		while (*p && ft_isspace((unsigned char)*p))
			p = p + 1;
		if (!(*p))
			break ;
		op_len = 0;
		if (is_operator(p, &op_len))
			p = process_operator(p, data);
		else
			p = process_word(p, g_shell, data);
	}
	return (data->state.token_count);
}

char	*alloc_t(const char *p, int len)
{
	char	*token;

	token = malloc(len + 1);
	if (!token)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_strncpy(token, p, len);
	token[len] = '\0';
	return (token);
}

const char	*process_operator(const char *p, t_tok_data *d)
{
	int		op_len;
	char	*op;

	op_len = 0;
	is_operator(p, &op_len);
	if (d->state.token_count == 0 && type_of_ope(p))
	{
		d->state.prev_redir = 1;
		return (p + op_len);
	}
	op = alloc_t(p, op_len);
	d->tokens[d->state.token_count] = op;
	d->cmd_flags[d->state.token_count] = -1;
	d->state.token_count = d->state.token_count + 1;
	if (ft_strcmp(op, "|") == 0)
	{
		d->state.has_command = 0;
		d->state.last_cmd_index = -1;
	}
	if (type_of_ope(op))
		d->state.prev_redir = 1;
	else
		d->state.prev_redir = 0;
	p = p + op_len;
	return (p);
}

const char	*handle_quote(const char *p, int *in_quote, char *qc)
{
	if (!(*in_quote))
	{
		*in_quote = 1;
		*qc = *p;
	}
	else if (*qc == *p)
	{
		*in_quote = 0;
		*qc = '\0';
	}
	return (p + 1);
}

const char	*collect_part(const char *p, char **part_out)
{
	const char	*start;
	int			in_quote;
	char		qc;
	int			op_len;

	start = p;
	in_quote = 0;
	qc = '\0';
	op_len = 0;
	while (*p)
	{
		if (*p == '\'' || *p == '\"')
		{
			p = handle_quote(p, &in_quote, &qc);
			continue ;
		}
		op_len = 0;
		if (!in_quote && is_operator(p, &op_len))
			break ;
		p = p + 1;
	}
	*part_out = alloc_t(start, p - start);
	return (p);
}

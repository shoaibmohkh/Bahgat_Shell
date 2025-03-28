/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 04:42:21 by marvin            #+#    #+#             */
/*   Updated: 2025/03/12 04:42:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_word	setup_word(char *part)
{
	t_word	w;
	char	*ts;
	char	*te;
	int		len;

	ts = 0;
	te = 0;
	ft_trim(part, &ts, &te);
	len = te - ts;
	w.ts = ts;
	w.te = te;
	w.len = len;
	return (w);
}

static void	handle_first_redir_remainder(t_word w, t_shell *g, t_tok_data *d)
{
	int		i;
	t_word	remainder;

	i = 0;
	while (i < w.len && !ft_isspace((unsigned char)w.ts[i]))
		i++;
	while (i < w.len && ft_isspace((unsigned char)w.ts[i]))
		i++;
	if (i < w.len)
	{
		remainder.ts = w.ts + i;
		remainder.te = w.te;
		remainder.len = w.len - i;
		process_normal_word(&remainder, g, d);
	}
}

static void	handle_first_redir(t_word w, t_shell *g, t_tok_data *d)
{
	int		i;
	t_word	operand;

	if (w.len > 1 && ((w.ts[0] == '\'' || w.ts[0] == '\"')
			&& (w.te[-1] == w.ts[0])))
	{
		process_redir_quoted(&w, g, d);
		return ;
	}
	i = 0;
	while (i < w.len && !ft_isspace((unsigned char)w.ts[i]))
		i++;
	operand.ts = w.ts;
	operand.te = w.ts + i;
	operand.len = i;
	if (operand.len > 0)
	{
		if (operand.len > 1 && ((operand.ts[0] == '\'' || operand.ts[0] == '\"')
				&& (operand.te[-1] == operand.ts[0])))
			process_redir_quoted(&operand, g, d);
		else
			process_redir_unquoted(&operand, g, d);
	}
	handle_first_redir_remainder(w, g, d);
}

static void	handle_redirection(t_word w, t_shell *g, t_tok_data *d)
{
	if (!d->state.has_command)
		handle_first_redir(w, g, d);
	else if (w.len > 1 && ((w.ts[0] == '\'' || w.ts[0] == '\"')
			&& (w.te[-1] == w.ts[0])))
		process_redir_quoted(&w, g, d);
	else
		process_redir_unquoted(&w, g, d);
}

const char	*process_word(const char *p, t_shell *g, t_tok_data *d)
{
	char	*part;
	t_word	w;

	part = NULL;
	p = collect_part(p, &part);
	w = setup_word(part);
	if (w.len <= 0)
	{
		free(part);
		d->state.prev_redir = 0;
		return (p);
	}
	if (d->state.prev_redir)
		handle_redirection(w, g, d);
	else
		process_normal_word(&w, g, d);
	free(part);
	return (p);
}

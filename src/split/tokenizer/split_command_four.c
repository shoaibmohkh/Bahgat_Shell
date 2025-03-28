/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command_four.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 04:44:08 by marvin            #+#    #+#             */
/*   Updated: 2025/03/15 02:42:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_redir_extra_if(t_rvars *r, t_word *w, t_shell *g, t_tok_data *d)
{
	(void)w;
	(void)g;
	r->old_len = ft_strlen(d->tokens[d->state.last_cmd_index]);
	r->merged = malloc(r->old_len + 1 + r->extra_len + 1);
	if (!r->merged)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_memcpy(r->merged, d->tokens[d->state.last_cmd_index], r->old_len);
	r->merged[r->old_len] = ' ';
	ft_memcpy(r->merged + r->old_len + 1, r->space, r->extra_len);
	r->merged[r->old_len + 1 + r->extra_len] = '\0';
	free(d->tokens[d->state.last_cmd_index]);
	d->tokens[d->state.last_cmd_index] = r->merged;
}

void	process_redir_extra_else(t_rvars *r, t_word *w, t_shell *g,
		t_tok_data *d)
{
	(void)w;
	(void)g;
	r->operand = malloc(r->extra_len + 1);
	if (!r->operand)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_strncpy(r->operand, r->space, r->extra_len);
	r->operand[r->extra_len] = '\0';
	d->tokens[d->state.token_count] = expander(r->operand, g);
	free(r->operand);
	d->cmd_flags[d->state.token_count] = 0;
	d->state.token_count = d->state.token_count + 1;
	d->state.has_command = 1;
	d->state.last_cmd_index = d->state.token_count - 1;
}

void	process_redir_extra(t_rvars *r, t_word *w, t_shell *g, t_tok_data *d)
{
	r->extra_len = w->te - r->space;
	if (d->state.has_command && d->state.last_cmd_index != -1
		&& d->cmd_flags[d->state.last_cmd_index] == 1)
		process_redir_extra_if(r, w, g, d);
	else
		process_redir_extra_else(r, w, g, d);
}

void	process_redir_word(t_word *w, t_shell *g, t_tok_data *d)
{
	if (w->len > 1 && ((w->ts[0] == '\'' || w->ts[0] == '\"')
			&& (w->te[-1] == w->ts[0])))
	{
		process_redir_quoted(w, g, d);
	}
	else
	{
		process_redir_unquoted(w, g, d);
	}
	d->state.prev_redir = 0;
}

void	process_normal_word(t_word *w, t_shell *g, t_tok_data *d)
{
	char	*word;

	(void)g;
	{
		word = malloc(w->len + 1);
		if (!word)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		ft_strncpy(word, w->ts, w->len);
		word[w->len] = '\0';
		d->tokens[d->state.token_count] = word;
		d->cmd_flags[d->state.token_count] = 1;
		d->state.token_count = d->state.token_count + 1;
		d->state.has_command = 1;
		d->state.last_cmd_index = d->state.token_count - 1;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command_three.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 04:42:52 by marvin            #+#    #+#             */
/*   Updated: 2025/03/12 04:42:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_redir_quoted(t_word *w, t_shell *g, t_tok_data *d)
{
	t_rvars	r;

	(void)g;
	r.operand = malloc(w->len - 1);
	if (!r.operand)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_strncpy(r.operand, w->ts + 1, w->len - 2);
	r.operand[w->len - 2] = '\0';
	d->tokens[d->state.token_count] = ft_strdup(r.operand);
	if (!d->tokens)
		handle_malloc_error();
	free(r.operand);
	d->cmd_flags[d->state.token_count] = 0;
	d->state.token_count++;
}

void	find_space(t_rvars *r, t_word *w)
{
	r->i = 0;
	r->space = 0;
	while (r->i < w->len)
	{
		if (ft_isspace((unsigned char)w->ts[r->i]))
		{
			r->space = w->ts + r->i;
			break ;
		}
		r->i = r->i + 1;
	}
}

void	process_redir_unquoted_branch(t_rvars *r, t_word *w, t_shell *g,
		t_tok_data *d)
{
	r->word_len = r->space - w->ts;
	r->operand = malloc(r->word_len + 1);
	if (!r->operand)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_strncpy(r->operand, w->ts, r->word_len);
	r->operand[r->word_len] = '\0';
	d->tokens[d->state.token_count] = expander(r->operand, g);
	free(r->operand);
	d->cmd_flags[d->state.token_count] = 0;
	d->state.token_count = d->state.token_count + 1;
	while (r->space < w->te && ft_isspace((unsigned char)*r->space))
		r->space = r->space + 1;
	if (r->space < w->te)
		process_redir_extra(r, w, g, d);
}

void	process_redir_unquoted_else(t_word *w, t_shell *g, t_tok_data *d)
{
	t_rvars	r;

	r.operand = malloc(w->len + 1);
	if (!r.operand)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_strncpy(r.operand, w->ts, w->len);
	r.operand[w->len] = '\0';
	d->tokens[d->state.token_count] = expander(r.operand, g);
	free(r.operand);
	d->cmd_flags[d->state.token_count] = 0;
	d->state.token_count = d->state.token_count + 1;
}

void	process_redir_unquoted(t_word *w, t_shell *g, t_tok_data *d)
{
	t_rvars	r;

	find_space(&r, w);
	if (r.space != 0)
		process_redir_unquoted_branch(&r, w, g, d);
	else
		process_redir_unquoted_else(w, g, d);
}

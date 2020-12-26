/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esoulard <esoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:18:44 by user42            #+#    #+#             */
/*   Updated: 2020/10/26 11:26:11 by esoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**Haven't used it yet, but will be useful during
**further cmd parsing
*/

static int	first_checks(t_sh *sh, int *i, int j)
{
	int		r;

	*i = pass_spaces(sh->in, *i);
	if ((j = parse_syntax(sh, *i)) == -1 && free_obj(&sh->obj) == -1)
		return (0);
	if (j == -2 || !(sh->obj = obj_new(sh->obj)))
		return (-1);
	if (!(sh->obj->redir = redir_new()))
		return (free_obj(&sh->obj));
	pipe_checks(sh, i);
	if ((sh->lev-- == 1) && (find_redir_err(sh, i) == -1)
	&& (g_err = 2) && free_obj(&sh->obj) == -1)
		return (0);
	if ((r = redir_loop(sh, i)) == -1)
	{
		g_err = 2;
		return (-1);
	}
	else if (r == -2 && sh->obj->pip != IS_PIPE && g_forked != IS_PIPE)
		return (0);
	if (sh->in[*i] && (r = parse_var(sh, i, 0)) == -1)
		return (free_obj(&sh->obj));
	else if (r == 1)
		return (2);
	return (1);
}

int			parse_ex_cond(t_sh *sh, int *i)
{
	int j;

	if ((j = parse_exec(sh, i)) == -1)
		return (free_obj(&sh->obj));
	else if (j == -2)
		general_loop(sh, i, 1);
	return (0);
}

static int	parse_sample(t_sh *sh, int *i, int stock, char *sample)
{
	int		j;

	if ((j = is_cmd(sample)) != -1)
	{
		if (!(init_obj(sh->obj, sample, j)))
			return (free_obj(&sh->obj));
		if (sh->obj->pip == IS_PIPE ||
		(sh->obj->prev && sh->obj->prev->pip == IS_PIPE))
		{
			if ((j = try_exec(NULL, sh, i)) == -1)
				return (0);
		}
		else if ((j = parse_cmds(sh, i)) == -1)
			return (1);
		if ((j = set_g_err(sh)) == 1)
			return (-1);
		else if (j == -2)
			general_loop(sh, i, 2);
	}
	else if ((*i = stock) == stock)
		if (parse_ex_cond(sh, i) == -1)
			return (-1);
	return (1);
}

int			general_loop(t_sh *sh, int *i, int lev)
{
	int		j;
	int		stock;
	char	*sample;

	sample = NULL;
	stock = *i;
	*i = pass_spaces(sh->in, *i);
	if (lev == 2)
		while (sh->in[*i])
			(*i)++;
	parse_all_var(sh, &sh->in, *i);
	if (!sh->in[*i] || is_end(sh->in, *i))
		return (1);
	if (!(sample = sample_str(sh, i, sample)))
		return (-1);
	if ((j = parse_sample(sh, i, stock, sample)) != 1
	&& free_str(sample))
		return (j);
	free(sample);
	if (lev == 0)
		*i = find_end(sh->in, *i);
	return (1);
}

int			general_parser(t_sh *sh)
{
	int			i;
	int			j;
	int			tmp;

	tmp = 0;
	if ((lonely_quote(sh->in) == -1) ||
		(last_backslash(sh->in) == -1))
	{
		ft_putstr_fd("bash: multi-line comments not supported\n", 2);
		return (0);
	}
	i = 0;
	j = 0;
	while (sh->in[i])
	{
		if ((j = first_checks(sh, &i, tmp)) < 1)
			return (j);
		else if (j == 2 && sh->in[i] && (++i))
			continue ;
		if (!sh->in[i] && free_obj(&sh->obj))
			continue ;
		if ((j = general_loop(sh, &i, 0)) != 1)
			return (j);
	}
	return (0);
}

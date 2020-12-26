/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:17:12 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 12:17:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**DUMMY PARSING FUNCTIONS
*/

int		parse_pwd(t_sh *sh, int *i)
{
	char	*workdir;
	int		r;

	workdir = NULL;
	while (sh->in[*i] && is_separator(sh->in, *i) == 0)
	{
		if ((r = find_redir(sh, i) == 0))
		{
			while (*i < (int)ft_strlen(sh->in)
			&& (is_separator(sh->in, *i) == 0))
			{
				if ((r = find_redir(sh, i) == 0))
					(*i)++;
				else if (r == -1)
					return (-1);
			}
		}
		else if (r == -1)
			return (-1);
	}
	workdir = get_pwd(sh->env);
	sh->obj->result = ft_strjoin_bth(workdir, ft_strdup("\n"));
	return (print_result(sh, 0, NULL));
}

int		parse_export(t_sh *sh, int *i)
{
	char	*sample;
	int		ret;
	int		stock_i;

	ret = 0;
	*i = pass_spaces(sh->in, *i);
	stock_i = *i;
	if (is_end(sh->in, *i) == 1)
		export_solo(sh);
	while (is_end(sh->in, *i) == 0)
	{
		if (redir_loop(sh, i) < 0)
			return (-1);
		if (!(sample = sample_str(sh, i, sample)))
			return (free_str(sample));
		if ((ret = sample_export(sample, sh->env, ret)) == -1)
			maj_err(sh, ft_sprintf(\
			"export: %s : not a valid identifier\n", sample), 1);
		free_str(sample);
		*i = pass_spaces(sh->in, *i);
	}
	if (ret == 2 && sh->in[stock_i] == '$')
		export_solo(sh);
	return (print_result(sh, 0, NULL));
}

int		parse_unset(t_sh *sh, int *i)
{
	char	**elt;
	char	*tmp;
	char	*sample;

	tmp = ft_strdup("");
	while (is_end(sh->in, *i) == 0)
	{
		if (redir_loop(sh, i) < 0)
			return (free_str(tmp));
		if (!(sample = sample_str(sh, i, sample)))
			return (free_two_str(sample, tmp));
		if (check_var(sample) != 0)
			maj_err(sh, ft_sprintf("unset: %s: not a valid identifier\n", \
			sample), 1);
		tmp = ft_strjoin_sp(tmp, sample);
	}
	if (!(elt = ft_split(tmp, ' ')))
		return (-1);
	free(tmp);
	unset_var(elt, sh);
	free_array(elt, -1, -1);
	return (print_result(sh, 0, NULL));
}

int		parse_env(t_sh *sh, int *i)
{
	int		r;

	*i = pass_spaces(sh->in, *i);
	while (is_end(sh->in, *i) == 0)
	{
		if ((r = find_redir(sh, i)) == 0)
		{
			while (*i < (int)ft_strlen(sh->in))
			{
				if ((r = find_redir(sh, i)) == 0)
					(*i)++;
				else if (r == -1)
					return (-1);
			}
			maj_err(sh, ft_strdup("env: too many arguments\n"), 1);
		}
		else if (r == -1)
			return (-1);
	}
	if (sh->obj->error)
		return (print_result(sh, 0, NULL));
	print_env(sh->env, sh->obj->redir->cmd_output);
	return (0);
}

int		parse_exit(t_sh *sh, int *i)
{
	char			*s;
	long long		r;

	s = NULL;
	r = 0;
	while (sh->in[*i])
	{
		if (redir_loop(sh, i) < 0)
			return (-1);
		if (is_end(sh->in, *i) == 1)
			break ;
		if (s != NULL && ((ft_numstr(s) != 1) || (r = 1)))
			*i = find_string_end(sh->in, *i);
		else if (s == NULL && !(s = sample_str(sh, i, s)))
			return (-1);
	}
	maj_err(sh, ft_sprintf("exit\n"), g_err);
	if ((r == 1) && (g_err = 1))
		maj_err(sh, ft_sprintf("exit: too many arguments\n"), 1);
	else if (s != NULL && ft_numstr(s) == 1 && chk_ll(s) == 0 &&
		(r = ft_atoi(s)))
		g_err = (r < 0 || r > 255) ? r % 256 : r;
	else if (s && (ft_numstr(s) != 1 || chk_ll(s) != 0) && (g_err = 2))
		maj_err(sh, ft_sprintf("exit: %s: numeric argument required\n", s), 2);
	return (print_result(sh, g_err, s));
}

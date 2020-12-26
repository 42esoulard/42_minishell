/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esoulard <esoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:20:35 by user42            #+#    #+#             */
/*   Updated: 2020/10/26 10:09:35 by esoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		check_vars(t_sh *sh, int i)
{
	int		j;
	char	*s;

	s = NULL;
	while (is_end(sh->in, i) == 0)
	{
		i = pass_spaces(sh->in, i);
		j = i;
		while (is_end(sh->in, j) == 0 && is_sp(sh->in, j) == 0
		&& sh->in[j] != '=' && sh->in[j] != '+')
			j++;
		if (sh->in[j] != '=' && pluseq(sh->in, j) == 0)
			return (i);
		if (pluseq(sh->in, j) == 1)
			j++;
		i = pass_spaces(sh->in, j + 1);
		if (is_end(sh->in, i) != 0)
			return (-2);
		if (!(s = sample_str(sh, &i, s)))
			return (-1);
		free(s);
		i = pass_spaces(sh->in, i);
	}
	return (-2);
}

int				replace_var_check(t_env *w, char *key, t_env *tru)
{
	char	*buf;
	char	*s;
	int		i;
	int		j;
	int		bs;

	i = -1;
	while ((w->val)[++i])
		if (w->val[i] == '$')
			if (ft_strncmp(&w->val[i + 1], key, ft_strlen(key)) == 0)
			{
				if (!(s = ft_substr(&w->val[i], 0, ft_strlen(key) + 1)))
					return (-1);
				j = 0;
				if (parse_sample_var(&s, &j, tru, &bs) < 0)
					return (free_str(s));
				if (!(buf = ft_strdup(&w->val[i + ft_strlen(key) + 1]))
				|| !(s = ft_strjoin_bth(s, buf))
				|| !(s = ft_strjoin_bth(ft_substr(w->val, 0, i), s)))
					return (-1);
				free(w->val);
				w->val = s;
				return (0);
			}
	return (0);
}

static int		check_var_inside(t_env *w, t_env *env)
{
	t_env	*tmp;

	tmp = w;
	while (tmp)
	{
		if (ft_strchr(tmp->val, '$'))
			if (check_var_loop(tmp, env, w))
				return (-1);
		tmp = tmp->next;
	}
	return (0);
}

static void		add_multiple_var(t_env *w, t_env *env)
{
	t_env	*tmp;

	while (w)
	{
		if ((tmp = find_env_entry(w->key, env)))
		{
			w->in = 1;
			if (w->pluseq == 1)
			{
				free(w->val);
				if (!(w->val_sp = ft_strjoin_bth(ft_strdup(tmp->val_sp), \
				w->val_sp)) || !(w->val = ft_strdup(w->val_sp)))
					return ;
			}
		}
		add_var(w, env);
		w = w->next;
	}
}

int				parse_var(t_sh *sh, int *i, int len)
{
	char	*to_split;
	char	**env_new;
	t_env	*wagon;
	t_env	*begin;
	int		ret;

	ret = check_vars(sh, *i);
	if (ret == -1 || (ret >= 0 && (*i = ret) > -1))
		return (0);
	len = *i;
	while (is_end(sh->in, len) == 0)
		len++;
	if (!(to_split = ft_substr(sh->in, *i, len - *i))
	|| !(env_new = ft_split_var(to_split, ' ', sh, i)))
		return (free_str(to_split));
	if (!(wagon = init_env(env_new, 0, 1)))
		return (free_array_and_str(env_new, -1, to_split) == 2);
	if ((begin = wagon) && check_var_inside(wagon, sh->env) < 0)
		return (free_array_and_str(env_new, -1, to_split) == 2);
	add_multiple_var(wagon, sh->env);
	free_array_and_str(env_new, -1, to_split);
	while (is_end(sh->in, *i) == 0)
		++(*i);
	env_clear(begin);
	return ((g_err = 0) ? 1 : 1);
}

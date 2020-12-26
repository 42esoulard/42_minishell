/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esoulard <esoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:18:01 by user42            #+#    #+#             */
/*   Updated: 2020/10/26 11:27:14 by esoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** sp = 1 == one space before
** sp = 2 == one space after
** sp = 3 == both
*/

int				split_val(char *s, int i)
{
	char	lev;
	int		sp;
	int		tmp;

	if (!(sp = 0) && is_sp(s, 0))
		sp = 1;
	lev = 0;
	while (i < (int)ft_strlen(s) && s[++i])
	{
		while (s[i] && is_sp(s, i) && lev == 0 && (i == 0 || is_sp(s, i - 1)))
			skim_str(s, i - 1, &tmp);
		lev = 0;
		if (is_quote(s, i, 0) && (lev = 1))
			while (i < (int)ft_strlen(s) && s[++i])
			{
				while (s[i] && !is_sp(s, i))
					++i;
				while (s[i] && !is_quote(s, i, 0) && is_sp(s, i + 1))
					skim_str(s, i, &tmp);
			}
	}
	i = (int)ft_strlen(s);
	if (i > 1 && is_sp(s, i - 1) && (sp = (sp == 1) ? 3 : 2))
		skim_str(s, i - 2, &tmp);
	return (sp);
}

static char		*put_quotes(char **s)
{
	char	**split;
	char	*tmp;
	int		i;

	i = -1;
	if (!(*s))
		return (0);
	if (!(split = ft_split(*s, ' ')))
		exit(EXIT_FAILURE);
	if (!(tmp = ft_strdup("")))
		exit(EXIT_FAILURE);
	while (split[++i])
	{
		if (!(split[i] = ft_strjoin_bth(ft_strdup("\""), split[i])))
			exit(EXIT_FAILURE);
		if (!(split[i] = ft_strjoin_bth(split[i], ft_strdup("\""))))
			exit(EXIT_FAILURE);
		if (!(tmp = ft_strjoin_sp(tmp, ft_strdup(split[i]))))
			exit(EXIT_FAILURE);
	}
	free_array(split, -1, 0);
	return (tmp);
}

static int		replace_var(char **sample, char *begin, t_env *elt, char *end)
{
	free(*sample);
	if ((g_err = 0) == 0 && !elt)
	{
		if (!(*sample = ft_strjoin_bth(begin, end)))
			return (free_two_str(begin, end));
		return (0);
	}
	if (begin[0] && (elt->sp == 1 || elt->sp == 3))
	{
		if (!(*sample = ft_strjoin_sp(begin, put_quotes(&elt->val))))
			return (free_two_str(begin, end));
	}
	else if (!(*sample = ft_strjoin_bth(begin, put_quotes(&elt->val))))
		return (free_two_str(begin, end));
	if (end[0] && elt->sp > 1)
	{
		if (!(*sample = ft_strjoin_sp(*sample, end)))
			return (free_two_str(*sample, end));
	}
	else if (!(*sample = ft_strjoin_bth(*sample, end)))
		return (free_two_str(*sample, end));
	return (0);
}

static int		parse_sample_var_mod(char **sample, int *j, t_env *env, int *r)
{
	char	*key;
	t_env	*elt;
	char	*begin;
	int		i;

	i = ++(*j) + 1;
	if (!(*sample)[*j] || normed_char((*sample)[*j]) == -1)
		return (-2);
	if (!ft_isdigit((*sample)[i - 1]) && (i -= 1))
		while (normed_char((*sample)[i]) == 0)
			i++;
	i -= *j;
	if (!(key = ft_substr(*sample, *j, i)))
		return (-1);
	*r += ft_strlen(key);
	if (!(elt = find_env_entry(key, env)) &&
	((*j) += (ft_strlen(key))) && free_str(key))
		return (-2);
	free(key);
	if (!(begin = ft_substr(*sample, 0, (*j) - 1)))
		return (-1);
	if (!(key = ft_substr(*sample, i + *j, ft_strlen(*sample))))
		return (free_str(begin));
	(*j)--;
	return (replace_var(sample, begin, elt, key));
}

void			parse_all_var(t_sh *sh, char **s, int i)
{
	int		tmp;

	tmp = 0;
	while (!is_end(*s, i) && (i = pass_spaces(*s, i)) > -1)
	{
		if (!is_end(*s, i) && (*s)[i] == '\\' && (*s)[i + 1] != '$')
			++i;
		if (!is_end(*s, i) && (*s)[i + 1] && (((*s)[i] == '$' &&
		(*s)[i + 1] == '?' && (i == 0 || (*s)[i - 1] != '\\')) ||
			((*s)[i] == '\\' && (*s)[i + 1] == '$')))
			i += 2;
		if (!is_end(*s, i) && (*s)[i] == '$' && (*s)[i + 1]
		&& (is_quote(*s, i + 1, 0)) && (++i))
			pass_quotes(sh, &i);
		while (!is_end(*s, i) && (*s)[i] == '$' &&
			normed_char((*s)[i + 1]) == 0)
			if (parse_sample_var_mod(&*s, &i, sh->env, &tmp) == -2)
				while (!is_end(*s, i) && !is_sp(*s, i)
				&& !is_quote(*s, i, 0))
					++i;
		if (!is_end(*s, i) && is_quote(*s, i, 0) == 1)
			pass_quotes(sh, &i);
		else if (!is_end(*s, i))
			++i;
	}
}

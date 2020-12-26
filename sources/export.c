/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:19:08 by user42            #+#    #+#             */
/*   Updated: 2020/10/24 19:12:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				unset_var(char **elt, t_sh *sh)
{
	int		i;

	i = -1;
	while (elt[++i])
	{
		if (ft_strcmp("_", elt[i]))
			del_from_key(&(sh->env), elt[i]);
	}
	return (0);
}

static int		process_export(char *sample, t_env *env, int in)
{
	t_env	*new;
	char	*trimmed;

	if (!(new = env_new(0)))
		return (-2);
	if (ft_strchr(sample, '='))
		in = 1;
	if (split_env(sample, new) == -1)
		return (-1);
	if (is_quote(new->val, 0, '\"') &&
	is_quote(new->val, ft_strlen(new->val) - 1, '\"'))
	{
		free(new->val);
		if (!(trimmed = ft_strtrim(new->val, "\"")))
			exit(EXIT_FAILURE);
		if (!(new->val = ft_strjoin_bth(ft_strdup("\\\""), trimmed)) ||
		!(new->val = ft_strjoin_bth(new->val, ft_strdup("\\\""))))
			exit(EXIT_FAILURE);
	}
	export_var(new, env, in);
	del_var(new);
	return (0);
}

int				sample_export(char *sample, t_env *env, int lev)
{
	int		i;
	int		ret;
	t_env	*tmp;

	i = -1;
	if (ft_isdigit(sample[0]) == 1)
		return (-1);
	if (!sample[0] && lev == 0)
		return (2);
	while (sample[++i] && sample[i] != '=' && sample[i] != '+')
		if (normed_char(sample[i]) != 0)
			return (-1);
	if (i == 0)
		return (-1);
	else if ((sample[i] == '+' && pluseq(sample, i) == 0))
		return (-1);
	if (!sample[i] && (tmp = find_env_entry(sample, env)))
		tmp->in = 1;
	else if (pluseq(sample, i) == 1)
		return (repluseq(sample, i, env, 1));
	else if ((ret = process_export(sample, env, 2)) < 0)
		return (ret);
	return (0);
}

int				add_var(t_env *elt, t_env *env)
{
	t_env	*tmp;
	t_env	*bis;

	tmp = env;
	if (!elt->key || !elt->val)
		return (-1);
	if (!(bis = find_env_entry(elt->key, env)))
	{
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = env_cpy(elt)))
			return (-1);
		return (0);
	}
	free(bis->val);
	free(bis->val_sp);
	bis->val = ft_strdup(elt->val);
	if (elt->val_sp)
		bis->val_sp = ft_strdup(elt->val_sp);
	else
		bis->val_sp = ft_strdup(elt->val);
	return (0);
}

int				export_var(t_env *elt, t_env *env, int in)
{
	t_env	*tmp;
	t_env	*bis;

	tmp = env;
	if (!elt->key || !elt->val)
		return (-1);
	if (!(bis = find_env_entry(elt->key, env)))
	{
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = env_cpy(elt)))
			return (-1);
		tmp->next->in = in;
		return (0);
	}
	free(bis->val);
	free(bis->val_sp);
	bis->val = ft_strdup(elt->val);
	bis->val_sp = ft_strdup(elt->val_sp);
	bis->in = 1;
	return (0);
}

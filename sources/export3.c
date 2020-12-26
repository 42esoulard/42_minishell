/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esoulard <esoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:18:59 by user42            #+#    #+#             */
/*   Updated: 2020/10/25 10:19:58 by esoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				pluseq(char *sample, int i)
{
	if (sample[i] == '+' && sample[i + 1] && sample[i + 1] == '=')
		return (1);
	return (0);
}

int				repluseq(char *sample, int i, t_env *env, int in)
{
	char	*key;
	char	*val;
	t_env	*elt;

	if (ft_isalnum(sample[i + 2]) == 0)
		return (-1);
	if (!(key = ft_substr(sample, 0, i)))
		return (-2);
	i += 2;
	if (!(val = ft_strdup(&sample[i])))
		return (-2);
	if (!(elt = find_env_entry(key, env)))
	{
		if (!(elt = env_new(in)))
			return (-2);
		elt->key = key;
		elt->val = val;
		export_var(elt, env, in);
		del_var(elt);
	}
	else if (free_str(key) == -1 &&
	(!(elt->val_sp = ft_strjoin_bth(elt->val_sp, val))
	|| !(elt->val = ft_strdup(elt->val_sp))))
		return (-2);
	return (0);
}

int				old_pwd(t_env *env)
{
	t_env	*old;
	char	*workdir;

	if (!(old = env_new(1)))
		return (-1);
	workdir = get_pwd(env);
	if (!(old->key = ft_strdup("OLDPWD")))
		return (env_clear(old));
	old->val = workdir;
	old->val_sp = ft_strdup(old->val);
	add_var(old, env);
	del_var(old);
	return (0);
}

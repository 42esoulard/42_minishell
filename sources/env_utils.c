/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:17:21 by user42            #+#    #+#             */
/*   Updated: 2020/10/22 12:10:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** lstnew for t_env
*/

t_env	*env_new(int in)
{
	t_env	*new;

	if (!(new = malloc(sizeof(t_env))))
		return (NULL);
	new->key = NULL;
	new->val = NULL;
	new->val_sp = NULL;
	new->in = in;
	new->sp = 0;
	new->next = NULL;
	new->pluseq = 0;
	return (new);
}

/*
** split key=val in 2 str, put them in a t_env elt
*/

int		split_env(char *line, t_env *elt)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (line[i] && line[i] != '=' && line[i] != '+')
		i++;
	if ((line[i] && line[i] == '+' && pluseq(line, i) == 0)
	|| !(elt->key = malloc(i + 1)))
		return (-1);
	while (++j < i)
		elt->key[j] = line[j];
	elt->key[j] = '\0';
	if (pluseq(line, i) == 1 && (elt->pluseq = 1))
		i++;
	if (!line[i] && !(elt->val = ft_strdup(&line[i])))
		return (-1);
	else if (line[i])
	{
		if (!(elt->val_sp = ft_strdup(&line[i + 1])) ||
		!(elt->val = ft_strdup(&line[i + 1])))
			return (-1);
		elt->sp = split_val(elt->val, -1);
	}
	return (0);
}

int		env_clear(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->val);
		free(env->val_sp);
		free(env);
		env = tmp;
	}
	return (-1);
}

void	print_env(t_env *env, int fd)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->in == 1)
			ft_dprintf(fd, "%s=%s\n", tmp->key, tmp->val_sp);
		tmp = tmp->next;
	}
}

/*
** conversion from char** to t_env*
** & check if in isn't corrupted
*/

t_env	*init_env(char **env, int in, int l)
{
	t_env	*lst;
	t_env	*tmp;
	int		i;
	int		lev;

	i = 0;
	lev = 0;
	if ((!env || !env[0]) && (lev = 1))
		env = empty_env();
	if (!(lst = env_new(in)))
		return (check_empty(lev, env));
	tmp = lst;
	if (lev == 1 && --i && find_path(lst) && env_clear(tmp) == 0)
		return (check_empty(lev, env));
	else if (lev == 0 && split_env(env[0], lst) == -1 && env_clear(tmp) == 0)
		return (check_empty(lev, env));
	while (env[++i])
	{
		if (!(lst->next = env_new(in)) && env_clear(tmp) == 0)
			return (check_empty(lev, env));
		lst = lst->next;
		if (split_env(env[i], lst) == -1 && env_clear(tmp) == 0)
			return (check_empty(lev, env));
	}
	return (old_empty(&tmp, l));
}

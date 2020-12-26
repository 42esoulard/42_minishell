/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:19:04 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 12:19:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*env_double(t_env *env)
{
	t_env	*new;

	if (!(new = malloc(sizeof(t_env))))
		return (NULL);
	new->key = ft_strdup(env->key);
	new->val = ft_strdup(env->val);
	new->in = 1;
	new->next = NULL;
	new->pluseq = 0;
	return (new);
}

static void		env_sort(t_env **env)
{
	t_env	*save;
	t_env	*elt;
	char	*tmp1;
	char	*tmp2;

	save = *env;
	while (save)
	{
		elt = *env;
		while (elt->next)
		{
			if (ft_strcmp(elt->key, elt->next->key) > 0)
			{
				tmp1 = elt->key;
				tmp2 = elt->val;
				elt->key = elt->next->key;
				elt->val = elt->next->val;
				elt->next->key = tmp1;
				elt->next->val = tmp2;
			}
			elt = elt->next;
		}
		save = save->next;
	}
}

static void		free_export(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->val);
		free(env->key);
		free(env);
		env = tmp;
	}
}

static void		print_export(int fd, t_env *env)
{
	t_env	*save;

	save = env;
	while (env)
	{
		if (env->val && env->val[0])
			ft_dprintf(fd, "declare -x %s=\"%s\"\n", env->key, env->val);
		else if (env->val)
			ft_dprintf(fd, "declare -x %s\n", env->key);
		else
		{
			free_export(save);
			return ;
		}
		env = env->next;
	}
	free_export(save);
}

void			export_solo(t_sh *sh)
{
	t_env	*ptr;
	t_env	*begin;
	t_env	*save;

	begin = sh->env;
	if (!sh->env || !sh->env->key)
		return ;
	while (begin && begin->in == 0)
		begin = begin->next;
	if (!begin || !(ptr = env_double(begin)))
		return ;
	save = ptr;
	while ((begin = begin->next))
	{
		if (begin->in > 0 && !(ptr->next = env_double(begin)))
		{
			free_export(save);
			return ;
		}
		if (begin->in > 0)
			ptr = ptr->next;
	}
	env_sort(&save);
	print_export(sh->obj->redir->cmd_output, save);
}

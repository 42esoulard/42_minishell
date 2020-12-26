/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esoulard <esoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:19:31 by user42            #+#    #+#             */
/*   Updated: 2020/11/05 14:05:56 by esoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			in_quotes(char *str, int i)
{
	char	tmp;
	int		j;
	int		count;

	j = i;
	count = 0;
	tmp = 0;
	while (--j >= 0 && str[j])
	{
		if (count == 0 && is_quote(str, j, 0) == 1)
		{
			tmp = str[j];
			count++;
		}
		else if (is_quote(str, j, tmp) == 1)
			count++;
	}
	if (count % 2 != 0)
		return (1);
	return (0);
}

char		*get_pwd(void *env)
{
	char	*workdir;

	if (!env || !(workdir = find_env_val("PWD", env))[0])
	{
		if (env)
			free(workdir);
		if (!(workdir = ft_calloc(PATH_MAX, 1)))
			return (NULL);
		if (getcwd(workdir, PATH_MAX) == NULL)
			return (char_free_str(workdir));
	}
	return (workdir);
}

static int	check_bis(t_env *w, t_env *tmp, t_env *env)
{
	t_env	*k;
	char	*ret;

	k = w;
	while (k)
	{
		if ((ret = ft_strnstr(tmp->val, k->key, ft_strlen(tmp->val))))
		{
			if (ret[ft_strlen(k->key)] == ':'
			|| is_end(ret, ft_strlen(k->key)))
			{
				if (replace_var_check(tmp, k->key, w) == -1)
					return (-1);
				if (replace_var_check(tmp, k->key, env) == -1)
					return (-1);
			}
		}
		k = k->next;
	}
	return (0);
}

int			check_var_loop(t_env *tmp, t_env *env, t_env *w)
{
	t_env	*j;
	char	*ret;

	j = env;
	while (j)
	{
		if ((ret = ft_strnstr(tmp->val, j->key, ft_strlen(tmp->val))))
		{
			if (ret[ft_strlen(j->key)] == ':'
			|| is_end(ret, ft_strlen(j->key)))
			{
				if (replace_var_check(tmp, j->key, env) == -1)
					return (-1);
				if (replace_var_check(tmp, j->key, w) == -1)
					return (-1);
			}
		}
		j = j->next;
	}
	if (check_bis(w, tmp, env) == -1)
		return (-1);
	return (0);
}

void		alt_skim(char **s, int *j, int *i)
{
	skim_str(*s, *j - 1, i);
	(*j)--;
	(*i)--;
}

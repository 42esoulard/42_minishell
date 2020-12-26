/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:16:58 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 12:16:59 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		remove_home_path(char **path, char *home)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	if (!home)
		return ;
	i = ft_strlen(home);
	if (ft_strncmp(*path, home, i) != 0)
		return ;
	if (!(tmp = malloc(ft_strlen(*path) - i + 2)))
		return ;
	tmp[0] = '~';
	i--;
	j = 0;
	while (++i <= ft_strlen(*path))
		tmp[++j] = (*path)[i];
	tmp[j] = '\0';
	free(*path);
	*path = tmp;
}

static int	check_permissions(t_stat st)
{
	if (st.st_mode & (S_IXUSR))
		return (0);
	return (1);
}

/*
** 0 and path NULL = permission denied
** 0 and path = go exec
** -1 = fatal error return -1 all the way to ms shutdown
** -2 = command not found return -2
*/

static int	sample_path(t_sh *sh, char *sample, char **path)
{
	t_stat	st;
	int		ret;

	ret = 0;
	if ((stat(sample, &st)) == 0 && S_ISDIR(st.st_mode) == 0)
	{
		if (check_permissions(st) == 0)
		{
			if (!(*path = ft_strdup(sample)))
				return (-1);
		}
		else if ((ret = -2) == -2)
			maj_err(sh, ft_sprintf("bash: %s: %s\n", sample, \
			"Permission denied"), 126);
	}
	else if (((stat(sample, &st)) != 0) && (ret = -2) == -2)
		maj_err(sh, ft_sprintf("bash: %s: %s\n", sample,
			strerror(errno)), 127);
	else if ((ret = -2) == -2)
		maj_err(sh, ft_sprintf("bash: %s: %s\n", sample, \
		"is a directory"), 126);
	if (ret != -2)
		return (print_result(sh, ret, NULL));
	else
		return (ret);
}

static int	loop_path(char *path_str, char **path, char *sample, t_sh *sh)
{
	t_stat	st;
	char	*test;

	if (!(test = ft_strjoin_slash(path_str, sample)))
		return (-1);
	if ((stat(test, &st)) == 0 && S_ISDIR(st.st_mode) == 0)
	{
		if (check_permissions(st) == 0)
		{
			if (!(*path = ft_strdup(test)))
				return (free_two_str(path_str, test));
		}
		else
			maj_err(sh, ft_sprintf("bash: %s: %s\n", sample, \
			"Permission denied"), 1);
		free(test);
		return (0);
	}
	free(test);
	return (-2);
}

int			check_path(t_sh *sh, char **path)
{
	char	**path_arr;
	char	*val;
	int		i;
	int		r;

	if ((i = -1) && ft_strchr(sh->obj->obj, '/'))
		return (sample_path(sh, sh->obj->obj, path));
	if (!(val = find_env_val("PATH", sh->env))[0])
		return (free_str(val));
	if (!(path_arr = ft_split(val, ':')))
		return (free_str(val));
	free(val);
	while (path_arr[++i])
		if ((r = loop_path(path_arr[i], path, sh->obj->obj, sh)) != -2)
		{
			if (r == -1)
				return (free_array(path_arr, -1, -1));
			break ;
		}
	if (free_array(path_arr, -1, -1) && r == -2)
	{
		maj_err(sh, ft_sprintf("%s: command not found\n", sh->obj->obj), 127);
		return (r);
	}
	return (print_result(sh, r, NULL));
}

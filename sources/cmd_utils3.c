/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esoulard <esoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:17:16 by user42            #+#    #+#             */
/*   Updated: 2020/10/25 10:42:01 by esoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**Cmd array init and strncmp with sample from in
**return appropriate index (corresponding to cmd function)
*/

int			is_cmd(char *sample)
{
	char	*cmds[8];
	int		j;

	cmds[0] = "echo";
	cmds[1] = "cd";
	cmds[2] = "pwd";
	cmds[3] = "export";
	cmds[4] = "unset";
	cmds[5] = "env";
	cmds[6] = "exit";
	cmds[7] = NULL;
	j = -1;
	while (cmds[++j] != NULL)
	{
		if ((ft_strlen(cmds[j]) == ft_strlen(sample)) &&
			ft_strncmp(cmds[j], sample, ft_strlen(sample)) == 0)
			return (j);
	}
	return (-1);
}

/*
**Cmds parsing functions array, and sends us to
**function corresponding to the matching index
**we got from strncmp
*/

int			parse_cmds(t_sh *sh, int *i)
{
	t_parse_cmd parse_cmd[7];
	int			ret;

	parse_cmd[0] = parse_echo;
	parse_cmd[1] = parse_cd;
	parse_cmd[2] = parse_pwd;
	parse_cmd[3] = parse_export;
	parse_cmd[4] = parse_unset;
	parse_cmd[5] = parse_env;
	parse_cmd[6] = parse_exit;
	if ((ret = parse_cmd[sh->obj->type](sh, i)) == -1)
	{
		while (is_end(sh->in, *i) == 0)
			(*i)++;
		if (sh->obj->pip == IS_PIPE || g_forked == IS_PIPE)
			exit(g_err);
		return (-1);
	}
	return (ret);
}

void		pass_option(t_sh *sh, int *i)
{
	while (is_end(sh->in, *i) == 0)
	{
		if ((ft_strncmp("-n", &sh->in[*i], 2) == 0 ||
			ft_strncmp("\\-n", &sh->in[*i], 3) == 0 ||
			ft_strncmp("-\\n", &sh->in[*i], 3) == 0)
			&& (is_end(sh->in, *i + 2) == 1
			|| is_sp(sh->in, *i + 2) == 1 ||
			only_n(sh->in, *i) == 1)
			&& ((*i) += 2))
			sh->obj->option = 1;
		else
			return ;
		if (sh->obj->option == 1 && sh->in[*i] && sh->in[*i] == 'n')
		{
			while (sh->in[*i] && (sh->in[*i] == 'n' || (sh->in[*i] == '\\' &&
				sh->in[*i + 1] && sh->in[*i + 1] == 'n')))
				(*i)++;
		}
		*i = pass_spaces(sh->in, *i);
	}
}

int			replace_pwd2(t_env *env, char **path, char **workdir)
{
	char *tmp;

	free(*workdir);
	if (!(tmp = find_env_val("PWD", env)))
		return (-1);
	if (!(*workdir = ft_strjoin_slash(tmp, *path)))
		return (-1);
	free_str(tmp);
	free_str(*path);
	*path = ft_strdup(*workdir);
	return (0);
}

int			replace_pwd(t_env *env, char **path)
{
	t_env	*pwd;
	char	*workdir;

	pwd = env_new(1);
	if (!(workdir = ft_calloc(PATH_MAX, 1)))
		return (-1);
	if ((getcwd(workdir, PATH_MAX) == NULL) && (ft_strncmp(*path, ".",
		ft_strlen(*path)) == 0 || ft_strncmp(*path, "..",
		ft_strlen(*path)) == 0))
	{
		if (replace_pwd2(env, path, &workdir) == -1)
			return (-1);
	}
	else if (getcwd(workdir, PATH_MAX) == NULL)
		return (free_str(workdir));
	if (!(pwd->val = ft_strdup(workdir))
	|| !(pwd->val_sp = ft_strdup(pwd->val)))
		return (free_str(workdir));
	if (!(pwd->key = ft_strdup("PWD")))
		return (free_str(workdir));
	free(workdir);
	add_var(pwd, env);
	del_var(pwd);
	return (0);
}

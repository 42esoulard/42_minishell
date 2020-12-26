/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esoulard <esoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:17:45 by user42            #+#    #+#             */
/*   Updated: 2020/10/25 09:50:49 by esoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			try_exec(char *tmp, t_sh *sh, int *i)
{
	pid_t	pid;
	int		lever;

	pid = -1;
	set_gfork(sh, tmp);
	lever = 0;
	if (sh->obj->pip == IS_PIPE)
	{
		lever = 1;
		if (pipe(sh->obj->tube) == -1)
			exit(EXIT_FAILURE);
	}
	if ((pid = fork()) < 0)
	{
		ft_dprintf(2, ft_sprintf("fork: %s\n", strerror(errno)));
		return (-1);
	}
	else if (pid == 0)
	{
		if (start_exec(tmp, sh, i))
			return (-1);
	}
	else
		handle_parent(pid, sh);
	return (0);
}

/*
** Putting potential params for the program in a char **av
*/

static char	**conv_av(t_sh *sh, int *i)
{
	int		j;
	char	**av;

	if (!(av = malloc(sizeof(char *) * (count_strings(sh->in, *i) + 2))))
		return (NULL);
	j = 0;
	if (!(av[j++] = ft_strdup(sh->obj->obj)))
		return (char_free_array(av, 0));
	while (is_end(sh->in, *i) == 0)
	{
		if (redir_loop(sh, i) < 0)
			return (char_free_array(av, j));
		if ((is_end(sh->in, *i) == 1))
			break ;
		if (!(av[j] = sample_str(sh, i, av[j])))
			return (char_free_array(av, j));
		j++;
	}
	av[j] = NULL;
	return (av);
}

static int	add_redirs(t_sh *sh, int *i)
{
	while (is_end(sh->in, *i) == 0)
	{
		if (redir_loop(sh, i) < 0)
			return (-1);
		if ((is_end(sh->in, *i) == 1))
			break ;
		*i = find_string_end(sh->in, *i);
	}
	return (0);
}

/*
** Had to add a structure containing both our env and bash env for lack of space
** (execve uses bash env as a param) (both_env is init in main).
** We make a sample with the potential program's
** name, make an argv with potential following args for the executable.
** We return -2 if no program was found, -1 in case of a fatal error.
*/

int			parse_exec_fk(char *path, t_sh *sh)
{
	if (try_exec(path, sh, 0) == -1)
		return (-1);
	return (0);
}

int			parse_exec(t_sh *sh, int *i)
{
	char	*path;
	int		stock_i;

	if ((path = NULL) == NULL && redir_loop(sh, i) == -1)
		return (-1);
	if (!(sh->obj->obj = sample_str(sh, i, sh->obj->obj)))
		return (-1);
	if (check_empty_var(sh, i))
		return (-2);
	stock_i = *i;
	if (add_redirs(sh, i) < 0 && sh->obj->pip != IS_PIPE && g_forked != IS_PIPE)
		return (0);
	if (sh->obj->fk == 1)
		return (parse_exec_fk(path, sh));
	if (check_path(sh, &path) == -2 && free_str(path))
		if (sh->obj->pip != IS_PIPE && (!(sh->obj->prev) ||
			sh->obj->prev->pip != IS_PIPE))
			return (print_result(sh, 0, NULL));
	if (!path)
		path = ft_strjoin("./", sh->obj->obj);
	if (!(sh->obj->charenv = env_to_array(sh->env)) ||
	!(sh->obj->args = conv_av(sh, &stock_i)) || try_exec(path, sh, 0) == -1)
		return (free_str(path));
	free(path);
	return (0);
}

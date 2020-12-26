/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esoulard <esoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:20:15 by user42            #+#    #+#             */
/*   Updated: 2020/10/21 19:25:01 by esoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				redir_loop(t_sh *sh, int *i)
{
	int		r;

	while ((r = find_redir(sh, i)) == 1 || r < 0)
	{
		if (r < 0)
			return (r);
	}
	return (0);
}

/*
** when parsing encounters wrong char/str (or no char)
** after a redir sign, finds it and prints error
*/

static int		redir_error(t_redir *redir, char *in, int *i, int j)
{
	char	*sym;
	int		k;

	k = 0;
	if (j > *i)
		sym = ft_substr(in, *i, j);
	else if (in[j] && in[j] == '>' && in[j + 1] == '>')
	{
		if (!(sym = ft_strdup(">>")))
			return (-1);
	}
	else if (!in[j] && !(sym = ft_strdup("newline")))
		return (-1);
	else if (in[j])
	{
		if (!(sym = ft_strdup("c")))
			return (-1);
		sym[0] = in[j];
	}
	ft_dprintf(redir->err_output, "bash: parse error near %s\n", sym);
	free(sym);
	return (-1);
}

static int		parse_redir(t_sh *sh, int *s_fd, int *i)
{
	int		j;
	char	*path;
	int		k;

	k = 0;
	path = NULL;
	if (s_fd[1] == 2)
		(*i)++;
	*i = pass_spaces(sh->in, *i);
	j = *i;
	free(sample_str(sh, &j, path));
	if (j == *i || is_redir(sh->in, j) != 0)
		return (redir_error(sh->obj->redir, sh->in, i, j));
	return (1);
}

int				find_redir_err(t_sh *sh, int *i)
{
	int		j;
	int		s_fd[2];

	s_fd[0] = 1;
	j = *i;
	while (is_end(sh->in, j) == 0 && (j = pass_spaces(sh->in, j)))
	{
		while (sh->in[j] && (s_fd[1] = is_redir(sh->in, j)) == 0
			&& ft_isdigit(sh->in[j]) == 0)
			j++;
		if (!sh->in[j])
			return (0);
		if (ft_isdigit(sh->in[j]) != 0)
			s_fd[0] = ft_atoi(&sh->in[j]);
		while (ft_isdigit(sh->in[j]) != 0)
			j++;
		if ((s_fd[1] = is_redir(sh->in, j)) != 0 && (j++)
			&& parse_redir(sh, s_fd, &j) < 0)
		{
			while (is_end(sh->in, *i) == 0)
				(*i)++;
			return (-1);
		}
	}
	return (0);
}

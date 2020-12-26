/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esoulard <esoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:18:53 by user42            #+#    #+#             */
/*   Updated: 2020/10/25 10:21:10 by esoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_gfork(t_sh *sh, char *tmp)
{
	if (sh->obj->pip == IS_PIPE || (sh->obj->prev &&
		sh->obj->prev->pip == IS_PIPE))
		g_forked = IS_PIPE;
	else if (tmp && is_ms(tmp) != 0)
		g_forked = IS_EXEC;
	else if (tmp && is_ms(tmp) == 0)
		g_forked = IS_F_MS;
	else
		g_forked = IS_MS;
	g_err = 0;
}

int		is_ms(char *exec)
{
	int i;

	i = ft_strlen(exec) - 1;
	while (exec[i] && exec[i] != '/')
		i--;
	if (i >= 0 && exec[i] == '/')
		i++;
	if (ft_strncmp(&exec[i], "minishell",
		ft_strlen(&exec[i])) == 0)
		return (0);
	return (1);
}

void	kill_pipe(int sig)
{
	int status;
	int ret;

	if (g_forked == IS_PIPE && g_pid != -1)
	{
		while ((ret = wait(&status)) != -1)
		{
			kill(g_pid, sig);
			if (ret == g_pid && sig == SIGINT)
				g_err = 130;
			else if (ret == g_pid && sig == SIGQUIT)
			{
				ft_dprintf(2, "Quit: Core dumped\n");
				g_err = 131;
			}
		}
	}
	g_pid = -1;
}

int		dup_exec(t_sh *sh)
{
	if (sh->obj->prev && sh->obj->prev->pip == IS_PIPE)
	{
		if (dup2(sh->obj->prev->tube[0], 0) == -1)
			return (-1);
		if (sh->obj->prev->tube[1] != -1)
			close(sh->obj->prev->tube[1]);
	}
	if (sh->obj->pip == IS_PIPE)
	{
		if (dup2(sh->obj->tube[1], 1) == -1)
			return (-1);
		if (sh->obj->tube[0] != -1)
			close(sh->obj->tube[0]);
	}
	if (sh->obj->redir->cmd_in >= 0 &&
	dup2(sh->obj->redir->cmd_in, 0) == -1)
		return (-1);
	if (sh->obj->redir->cmd_output >= 1 &&
	dup2(sh->obj->redir->cmd_output, 1) == -1)
		return (-1);
	return (0);
}

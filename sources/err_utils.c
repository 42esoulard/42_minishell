/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esoulard <esoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:17:50 by user42            #+#    #+#             */
/*   Updated: 2020/10/26 11:25:11 by esoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		set_g_err(t_sh *sh)
{
	if (!sh->obj || !sh->obj->obj)
		return (0);
	if (sh->obj && sh->obj->obj && (strncmp(sh->obj->obj, "exit",
		ft_strlen(sh->obj->obj)) == 0) && !ft_strstr(sh->obj->error,
		"too many") && sh->obj->pip != IS_PIPE && g_forked != IS_PIPE)
		return (1);
	if (sh->obj && sh->obj->obj && (strncmp(sh->obj->obj, "exit",
		ft_strlen(sh->obj->obj)) == 0) && ft_strstr(sh->obj->error,
		"too many") && sh->obj->pip != IS_PIPE && g_forked != IS_PIPE)
		return (-2);
	if (!(sh->obj->error) && strncmp(sh->obj->obj, "exit",
		ft_strlen(sh->obj->obj)) != 0 && g_forked != IS_PIPE)
		g_err = 0;
	return (0);
}

int		parse_g_err(char **sample, int *l, int *i)
{
	char	*val;
	char	*begin;
	char	*end;

	skim_str(*sample, (*l) - 1, i);
	skim_str(*sample, (*l) - 1, i);
	if (!(val = ft_itoa(g_err)))
		return (-1);
	if (!(begin = ft_substr(*sample, 0, (*l))))
		return (free_str(val));
	if (!(end = ft_substr(*sample, *l, ft_strlen(*sample))))
		return (free_two_str(val, begin));
	free(*sample);
	if (!(*sample = ft_strjoin_bth(begin, val)))
	{
		free(end);
		return (free_two_str(begin, val));
	}
	if (!(*sample = ft_strjoin_bth(*sample, end)))
		return (free_two_str(*sample, end));
	return (0);
}

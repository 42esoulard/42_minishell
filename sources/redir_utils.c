/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:20:10 by user42            #+#    #+#             */
/*   Updated: 2020/10/21 16:04:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				is_end(char *str, int i)
{
	if (!str[i] || is_separator(str, i) == 1)
		return (1);
	return (0);
}

/*
** returns 1 if >, 2 if >>, 3 if <
*/

static int		quote_redir(char *str, int i)
{
	if (i > 1 && (ft_strncmp(&str[i - 2], "\'>>", 3) == 0
		|| ft_strncmp(&str[i - 2], "\">>", 3) == 0))
		return (1);
	if (i > 0 && (ft_strncmp(&str[i - 1], "\'>", 2) == 0
		|| ft_strncmp(&str[i - 1], "\'>>", 3) == 0
		|| ft_strncmp(&str[i - 1], "\'<", 2) == 0
		|| ft_strncmp(&str[i - 1], "\">", 2) == 0
		|| ft_strncmp(&str[i - 1], "\">>", 3) == 0
		|| ft_strncmp(&str[i - 1], "\"<", 2) == 0))
		return (1);
	if (ft_strncmp(&str[i], "\'>", 2) == 0
		|| ft_strncmp(&str[i], "\'>>", 3) == 0
		|| ft_strncmp(&str[i], "\'<", 2) == 0
		|| ft_strncmp(&str[i], "\">", 2) == 0
		|| ft_strncmp(&str[i], "\">>", 3) == 0
		|| ft_strncmp(&str[i], "\"<", 2) == 0)
		return (1);
	return (0);
}

int				is_redir(char *str, int i)
{
	if (quote_redir(str, i) == 1)
		return (0);
	if (str[i] == '>' || str[i] == '<')
	{
		if ((i > 0) && (str[i - 1] == '\\'))
			return (0);
		if (str[i] == '>' && str[i + 1] == '>')
			return (2);
		if (str[i] == '>')
			return (1);
		return (3);
	}
	return (0);
}

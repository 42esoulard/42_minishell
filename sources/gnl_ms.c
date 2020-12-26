/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_ms.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esoulard <esoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 12:42:15 by esoulard          #+#    #+#             */
/*   Updated: 2020/10/21 20:52:15 by esoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static int	free_sfd(char *str)
{
	free(str);
	return (0);
}

char		*give_it_back_ms(char *str, char **line)
{
	int		len;
	char	*result;

	len = 0;
	result = NULL;
	while (str[len] && str[len] != '\n')
		len++;
	*line = ft_strndup(str, len);
	if (str[len] && str[len + 1])
		result = ft_strdup(&str[len + 1]);
	free(str);
	str = NULL;
	return (result);
}

int			gnl_ms(int fd, char **line)
{
	static char	*s[FOPEN_MAX];
	char		buffer[31];
	int			i;

	if (!line || fd < 0 || (read(fd, 0, 0)) < 0)
		return (-1);
	if (s[fd] == NULL)
		s[fd] = ft_strdup("");
	i = 0;
	while (ft_strchr(s[fd], '\n') || (i = read(fd, buffer, 30)) >= 0)
	{
		if (g_sigint == 1 && (g_sigint = 0) == 0)
			s[fd][0] = '\0';
		if ((buffer[i] = '\0') == 0 && i == 0 && ft_strlen(s[fd]) == 0)
			return (free_sfd(s[fd]));
		if (!(s[fd] = ft_gnl_strjoin(s[fd], buffer)))
			return (-1);
		if ((ft_strchr(s[fd], '\n') && ++i))
			break ;
	}
	if (((g_sigint = 0) == 0) && i >= 0)
		s[fd] = give_it_back(s[fd], line);
	if (i > 0)
		return (1);
	return (i);
}

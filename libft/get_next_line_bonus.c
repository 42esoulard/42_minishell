/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:16:21 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 12:16:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*give_it_back(char *str, char **line)
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
	return (result);
}

int		get_next_line(int fd, char **line)
{
	static char	*s[FOPEN_MAX];
	char		buffer[31];
	int			i;

	if (!line || fd < 0 || (read(fd, 0, 0)) < 0)
		return (-1);
	if (s[fd] == NULL)
		s[fd] = ft_strdup("");
	i = 0;
	while (ft_strchr(s[fd], '\n') || (i = read(fd, buffer, 30)) > 0)
	{
		buffer[i] = '\0';
		if (!(s[fd] = ft_gnl_strjoin(s[fd], buffer)))
			return (-1);
		if (ft_strchr(s[fd], '\n') && ++i)
			break ;
	}
	if (i >= 0)
		s[fd] = give_it_back(s[fd], line);
	if (i > 0)
		return (1);
	return (i);
}

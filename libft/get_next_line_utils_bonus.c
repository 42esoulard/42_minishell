/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:16:16 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 12:16:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_strjoin(char *s1)
{
	free(s1);
	s1 = NULL;
}

char		*ft_gnl_strjoin(char *s1, char *s2)
{
	char	*new;
	int		s1len;
	int		i;
	int		j;

	s1len = 0;
	i = -1;
	j = 0;
	new = NULL;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	while (s1[s1len])
		s1len++;
	while (s2[j])
		j++;
	if (!(new = malloc(sizeof(char) * (s1len + j + 1))))
		return (NULL);
	while (s1[++i])
		new[i] = s1[i];
	j = 0;
	while (s2[j])
		new[i++] = s2[j++];
	new[i] = '\0';
	free_strjoin(s1);
	return (new);
}

char		*ft_strndup(const char *s1, int len)
{
	char	*cpy;
	int		i;

	if (!(cpy = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (s1[i] && i < len)
	{
		cpy[i] = s1[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

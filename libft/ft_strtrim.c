/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:11:37 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 12:11:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		trim_start(char const *s1, char const *set)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (set[i] && s1[j])
	{
		if (s1[j] == set[i])
		{
			i = -1;
			j++;
		}
		i++;
	}
	return (j);
}

static int		trim_end(char const *s1, char const *set, int j)
{
	int i;
	int k;

	i = 0;
	k = (int)ft_strlen(s1) - 1;
	if ((int)ft_strlen(s1) == j)
		return (k);
	while (set[i] && s1[k])
	{
		if (s1[k] == set[i])
		{
			i = -1;
			k--;
		}
		i++;
	}
	return (k);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	int		i;
	int		j;
	int		k;

	trimmed = NULL;
	if (!s1 || !set)
		return (NULL);
	j = trim_start(s1, set);
	k = trim_end(s1, set, j);
	if (!(trimmed = malloc(sizeof(char) * ((k - j) + 2))))
		return (NULL);
	i = 0;
	while (s1[j] && j <= k)
		trimmed[i++] = s1[j++];
	trimmed[i] = '\0';
	return (trimmed);
}

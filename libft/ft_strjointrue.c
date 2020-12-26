/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjointrue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:12:27 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 12:12:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		i;
	int		j;

	i = -1;
	j = 0;
	new = NULL;
	if ((s1 == NULL || s2 == NULL))
		return (NULL);
	while (s2[j])
		j++;
	if (!(new = malloc(sizeof(char) * (ft_pstrlen(s1) + j + 1))))
		return (NULL);
	while (s1[++i])
		new[i] = s1[i];
	j = 0;
	while (s2[j])
		new[i++] = s2[j++];
	new[i] = '\0';
	return (new);
}

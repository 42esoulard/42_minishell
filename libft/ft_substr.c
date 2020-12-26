/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:11:30 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 12:11:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (!(new = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (start > ft_pstrlen(s))
	{
		new[0] = '\0';
		return (new);
	}
	while (s[start] && i < len)
		new[i++] = s[start++];
	new[i] = '\0';
	return (new);
}

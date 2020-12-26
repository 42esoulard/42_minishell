/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:14:33 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 12:14:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t				i;
	unsigned char		*convsrc;
	unsigned char		*convdst;
	unsigned char		needle;

	i = 0;
	convsrc = (unsigned char *)src;
	convdst = (unsigned char *)dst;
	needle = (unsigned char)c;
	while (i < n)
	{
		convdst[i] = convsrc[i];
		if (convsrc[i] == needle)
			return (&convdst[i + 1]);
		i++;
	}
	return (NULL);
}

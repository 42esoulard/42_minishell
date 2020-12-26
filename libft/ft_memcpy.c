/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:14:15 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 12:14:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*dstcast;
	char	*srccast;

	i = 0;
	if (dst == src || n == 0)
		return (dst);
	dstcast = (char *)dst;
	srccast = (char *)src;
	while (i < n)
	{
		dstcast[i] = srccast[i];
		i++;
	}
	return (dstcast);
}

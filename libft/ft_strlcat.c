/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:12:22 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 12:12:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t i;
	size_t j;
	size_t srclen;
	size_t dstlen;

	i = 0;
	j = 0;
	srclen = ft_pstrlen(src);
	while (dst[i] != '\0' && i < dstsize)
		i++;
	dstlen = i;
	if (dstlen >= dstsize)
		return (srclen + dstsize);
	while (dstsize > 0 && i < (dstsize - 1) && src[j] != '\0')
	{
		dst[i] = src[j++];
		i++;
	}
	dst[i] = '\0';
	return (dstlen + srclen);
}

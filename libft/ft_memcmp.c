/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:14:22 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 12:14:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*c_s1;
	unsigned char	*c_s2;

	c_s1 = (unsigned char *)s1;
	c_s2 = (unsigned char *)s2;
	i = 0;
	if (!c_s1 && !c_s2)
		return (0);
	while (i < n)
	{
		if (c_s1[i] != c_s2[i])
			return (c_s1[i] - c_s2[i]);
		i++;
	}
	return (0);
}

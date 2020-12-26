/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:14:28 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 12:14:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*c_str;
	unsigned char	c_c;

	c_str = (unsigned char *)s;
	c_c = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (c_str[i] == c_c)
			return (&c_str[i]);
		i++;
	}
	return (NULL);
}

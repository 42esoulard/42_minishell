/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:11:42 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 12:11:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*haystack;
	char	needle;
	int		len;

	haystack = (char *)s;
	needle = (char)c;
	len = 0;
	while (haystack[len])
		len++;
	if (needle == '\0' && haystack[len] == '\0')
		return (&haystack[len]);
	while (len >= 0)
	{
		if (haystack[len] == needle)
			return ((char *)s + len);
		len--;
	}
	return (NULL);
}

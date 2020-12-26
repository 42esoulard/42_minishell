/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:11:46 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 12:11:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*haycast;

	haycast = (char *)haystack;
	i = 0;
	if (!needle[0])
		return (haycast);
	while (haycast[i] && i < len)
	{
		j = 0;
		while (haycast[i + j] && needle[j]
			&& haycast[i + j] == needle[j] && (i + j) < len)
			j++;
		if (!(needle[j]))
			return (&haycast[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;
	char	*haycast;

	if (!haystack)
		return (NULL);
	haycast = (char *)haystack;
	i = 0;
	if (!needle[0])
		return (haycast);
	while (haycast[i])
	{
		j = 0;
		while (haycast[i + j] && needle[j]
			&& haycast[i + j] == needle[j])
			j++;
		if (!(needle[j]))
			return (&haycast[i]);
		i++;
	}
	return (NULL);
}

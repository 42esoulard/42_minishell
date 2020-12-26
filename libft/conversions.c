/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:08:01 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 12:08:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*null_str(char *ret)
{
	if (!(ret = malloc(sizeof(char) * 9)))
		return (NULL);
	ret = ft_memcpy(ret, "R1(null)", 9);
	return (ret);
}

char	*convert_char(char *ret, va_list ap)
{
	char c;

	c = va_arg(ap, int);
	if (!(ret = malloc(sizeof(char) * 4)))
		return (NULL);
	ret[0] = 'C';
	if (c == 0)
	{
		c = -11;
		ret[1] = '2';
	}
	else
		ret[1] = '1';
	ret[2] = c;
	ret[3] = '\0';
	return (ret);
}

char	*convert_str(char *ret, va_list ap)
{
	char *str;

	str = va_arg(ap, char *);
	if (!str)
		return (null_str(ret));
	else
	{
		if (!(ret = malloc(sizeof(char) * (ft_pstrlen(str) + 3))))
			return (NULL);
		ret[0] = 'R';
		ret[1] = '1';
		ret[2] = '\0';
		ft_strlcat(ret, str, (ft_pstrlen(str) + 3));
	}
	return (ret);
}

char	*convert_signed_int(char *ret, va_list ap)
{
	char *str;

	str = ft_itoa(va_arg(ap, int));
	if (!str)
		return (null_str(ret));
	else
	{
		if (!(ret = malloc(sizeof(char) * (ft_pstrlen(str) + 3))))
			return (NULL);
		ret[0] = 'R';
		ret[1] = '1';
		ret[2] = '\0';
		ft_strlcat(ret, str, (ft_pstrlen(str) + 3));
		free(str);
	}
	return (ret);
}

char	*convert_unsigned_int(char *ret, va_list ap)
{
	char *str;

	str = ft_unsigned_itoa((int)va_arg(ap, unsigned int));
	if (!str)
		return (null_str(ret));
	else
	{
		if (!(ret = malloc(sizeof(char) * (ft_pstrlen(str) + 3))))
			return (NULL);
		ret[0] = 'R';
		ret[1] = '1';
		ret[2] = '\0';
		ft_strlcat(ret, str, (ft_pstrlen(str) + 3));
		free(str);
	}
	return (ret);
}

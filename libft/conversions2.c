/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:08:11 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 12:08:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*base_are_belong(char d)
{
	if (d == 'p' || d == 'x')
		return ("0123456789abcdef");
	else if (d == 'X')
		return ("0123456789ABCDEF");
	return (NULL);
}

char	*ft_putlnbr_base(unsigned long long lnbr, char d, char *str)
{
	unsigned long long	i;
	int					j;
	int					kazbaz;
	int					size;

	kazbaz = 0;
	j = 0;
	i = 1;
	size = 1;
	while ((lnbr / i) >= (unsigned long long)ft_pstrlen(base_are_belong(d)))
	{
		i = i * (unsigned long long)ft_pstrlen(base_are_belong(d));
		size++;
	}
	if (!(str = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (i > 0)
	{
		kazbaz = (lnbr / i) % (unsigned long
			long)ft_pstrlen(base_are_belong(d));
		str[j++] = base_are_belong(d)[kazbaz];
		i = i / (unsigned long long)ft_pstrlen(base_are_belong(d));
	}
	str[j] = '\0';
	return (str);
}

char	*convert_addr(char *ret, va_list ap)
{
	char	*addr;
	int		i;
	int		j;

	addr = NULL;
	addr = ft_putlnbr_base((unsigned long long)va_arg(ap, void *), 'p', addr);
	if (!addr)
		return (null_str(ret));
	else
	{
		if (!(ret = malloc(sizeof(char) * (ft_pstrlen(addr) + 5))))
			return (NULL);
		i = -1;
		j = 0;
		ret[j++] = 'R';
		ret[j++] = '1';
		ret[j++] = '0';
		ret[j++] = 'x';
		while (addr[++i])
			ret[j++] = addr[i];
		ret[j] = '\0';
	}
	free(addr);
	return (ret);
}

char	*convert_unsigned_hexa(char *ret, va_list ap, char d)
{
	char			*str;
	unsigned int	bli;

	bli = va_arg(ap, unsigned int);
	str = NULL;
	str = ft_putlnbr_base((unsigned long long)bli, d, str);
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

char	*convert_percent(char *ret, int *i)
{
	if (!(ret = malloc(sizeof(char) * 4)))
		return (NULL);
	ret[0] = 'R';
	ret[1] = '1';
	ret[2] = '%';
	ret[3] = '\0';
	(*i)--;
	return (ret);
}

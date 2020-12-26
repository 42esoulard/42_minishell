/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:12:04 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 12:12:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_pstrlen(const char *s)
{
	size_t len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int		actual_len(char *ret)
{
	int len;

	len = 0;
	while (ret[len])
		len++;
	return (len - 2);
}

int		eligible_for_empty_str(char *arg, int conv, int precision, char *ret)
{
	if (arg[conv] == 's' || ((precision == 0 || precision == -2) &&
		zero_chain(ret, arg[conv]) == 1 && (arg[conv] == 'u' ||
			arg[conv] == 'd' || arg[conv] == 'i' || arg[conv] == 'x'
				|| arg[conv] == 'X' || arg[conv] == 'p')))
		return (1);
	return (0);
}

int		give_precision_a_damn_len(char *ret)
{
	int len;

	len = actual_len(ret) - 1;
	if (ret[2] == '-' && ft_isdigit(ret[3]) == 1)
		len--;
	return (len);
}

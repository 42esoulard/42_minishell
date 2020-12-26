/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:15:32 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 12:15:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_type(char *arg, int i)
{
	if (arg[i] == 'c' || arg[i] == 's' || arg[i] == 'p' || arg[i] == 'd'
		|| arg[i] == 'i' || arg[i] == 'u' || arg[i] == 'x' || arg[i] == 'X'
		|| arg[i] == '%')
		return (1);
	return (0);
}

int		parse_end_format(char *arg, int i)
{
	if (!arg[i])
		return (i);
	while (arg[i] && is_type(arg, i) != 1)
		i++;
	return (i + 1);
}

int		zero_chain(char *ret, char type)
{
	int i;

	i = 2;
	if (type == 'p')
		i = 4;
	while (ret[i] && ret[i] == '0')
		i++;
	if (i != 2 && !ret[i])
		return (1);
	return (0);
}

int		check_dash_flag(char *arg, int i)
{
	if (arg[i] == '%')
		i--;
	while (arg[i] != '%')
		i--;
	i++;
	while (is_type(arg, i) == 0 && (ft_isdigit(arg[i]) == 0 || arg[i] == '0'))
	{
		if (arg[i] == '-')
			return (1);
		i++;
	}
	return (0);
}

int		check_zero_filler(char *arg, int i)
{
	if (arg[i] == '%')
		i--;
	while (arg[i] != '%')
		i--;
	i++;
	if (arg[i] && arg[i] == '0')
		return (1);
	else
		return (0);
}

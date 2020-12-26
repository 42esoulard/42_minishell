/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:16:03 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 12:16:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	**init_tab(char *arg, char **stock)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (arg[i])
	{
		if (arg[i] && arg[i] != '%')
		{
			count++;
			while (arg[i] && arg[i] != '%')
				i++;
		}
		if (arg[i] && arg[i] == '%')
		{
			count++;
			i = parse_end_format(arg, i);
		}
	}
	if (!(stock = malloc(sizeof(char *) * (count + 1))))
		return (NULL);
	return (stock);
}

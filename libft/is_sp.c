/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:15:50 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 12:15:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		is_sp(char *str, int i)
{
	int count;

	count = 0;
	if (str[i] == '\f' || str[i] == '\n' || str[i] == '\r' ||
		str[i] == '\t' || str[i] == '\v' || str[i] == ' ')
	{
		if ((i > 0) && (str[i - 1] == '\\'))
		{
			while (str[--i] && str[i] == '\\')
				count++;
			if (count % 2 != 0)
				return (0);
		}
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_llong.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:07:52 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 12:07:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		chk_ll(char *str)
{
	char	*max;
	char	sign;
	int		len;
	int		i;

	i = 0;
	if ((sign = '+') && (str[i] == '+' || str[i] == '-'))
		sign = str[i++];
	while (str[i] == '0')
		i++;
	len = ft_strlen(str);
	if ((len - i) > 19)
		return (1);
	if ((len - i) < 19)
		return (0);
	max = ft_strdup("922337203685477580");
	len = 0;
	while (str[i] && len < 18)
		if (str[i++] > max[len++])
			return (free_str(max));
	if (str[i] && ((sign == '+' && str[i] > '7') ||
		(sign == '-' && str[i] > '8')))
		return (free_str(max));
	free_str(max);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:12:54 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 12:12:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*go_sprint(char **result, char **stock)
{
	int		i;
	int		len;
	int		ratlen;
	int		stocklen;
	char	*rat;

	rat = NULL;
	len = calculatelen(stock);
	stocklen = 0;
	rat = ft_replace_replaceable(stock[0], &stocklen, 2);
	ratlen = stocklen;
	i = 1;
	while (stock[i])
	{
		rat = ft_printf_strjoin(rat, ft_replace_replaceable(stock[i],
			&stocklen, 2), stocklen, ratlen);
		ratlen += stocklen;
		i++;
	}
	free(stock);
	*result = ft_strdup(rat);
	free(rat);
	return (*result);
}

char	*ft_sprintf(const char *arg, ...)
{
	va_list	ap;
	char	**stock;
	char	*cpyarg;
	int		i;
	char	*result;

	stock = NULL;
	cpyarg = NULL;
	if (arg[1] == '\0')
		return (0);
	cpyarg = ft_strdup(arg);
	stock = init_tab(cpyarg, stock);
	va_start(ap, arg);
	i = 0;
	if (stock != NULL)
		fill_tab(stock, &cpyarg, ap, i);
	free(cpyarg);
	va_end(ap);
	return (go_sprint(&result, stock));
}

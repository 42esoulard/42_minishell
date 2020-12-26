/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:15:22 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 12:15:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		calculatelen(char **str)
{
	int i;
	int j;
	int len;

	i = 0;
	len = 0;
	while (str[i])
	{
		j = 2;
		while (str[i][j])
		{
			j++;
			len++;
		}
		i++;
	}
	return (len);
}

char	*ft_replace_replaceable(char *str, int *stocklen, int i)
{
	int		j;
	char	*newstr;

	newstr = NULL;
	if (!str)
		return (NULL);
	*stocklen = actual_len(str);
	if (str[0] == 'R')
		newstr = ft_substr(str, 2, actual_len(str));
	else if (str[0] == 'C')
	{
		if (!(newstr = malloc(sizeof(char) * (actual_len(str) + 1))))
			return (NULL);
		j = 0;
		while (j <= *stocklen)
		{
			if (str[1] == '2' && str[i] == -11)
				str[i] = '\0';
			newstr[j++] = str[i++];
		}
		newstr[j] = '\0';
	}
	free(str);
	return (newstr);
}

int		go_print(char **stock)
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
	write(1, rat, ratlen);
	free(stock);
	free(rat);
	return (len);
}

int		cstrlen(char *arg, int i)
{
	int strlen;

	strlen = 0;
	while (arg[i] && arg[i] != '%')
	{
		strlen++;
		i++;
	}
	return (strlen);
}

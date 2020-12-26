/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:15:17 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 12:15:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		check_width(char *arg, int i)
{
	int start;
	int width;

	width = 0;
	while (arg[i] != '%')
		i--;
	i++;
	while ((is_type(arg, i) == 0 && arg[i] != '.' && ft_isdigit(arg[i]) == 0)
		|| arg[i] == '0' || arg[i] == '-')
		i++;
	if (ft_isdigit(arg[i]) == 1)
	{
		start = i;
		while (ft_isdigit(arg[i]) == 1)
			i++;
		while (start < i)
			width = width * 10 + (arg[start++] - 48);
		return (width);
	}
	return (-1);
}

char	*to_dash(char *ret, char *newret, char c, int min_width)
{
	int j;
	int k;

	j = 0;
	k = 0;
	while (ret[k])
		newret[j++] = ret[k++];
	while (j - 2 < min_width)
		newret[j++] = c;
	newret[j] = '\0';
	free(ret);
	return (newret);
}

char	*well_actually_dash(char *ret, int min_width)
{
	int		j;
	int		k;
	char	*newret;

	k = 0;
	j = 0;
	newret = NULL;
	if (!(newret = malloc(sizeof(char) * (min_width + 3))))
		return (NULL);
	while (k < 3)
		newret[j++] = ret[k++];
	return (newret);
}

char	*not_to_dash(char *ret, char *newret, char c, int min_width)
{
	int j;
	int k;
	int len;

	j = 0;
	k = 0;
	len = actual_len(ret);
	while (k < 2)
		newret[j++] = ret[k++];
	if (ret[k] == '-' && ft_isdigit(ret[k + 1]) == 1 && c == '0')
	{
		len--;
		free(newret);
		newret = well_actually_dash(ret, min_width);
		j = 3;
		k = 3;
	}
	while (j - 2 < (min_width - len))
		newret[j++] = c;
	while (ret[k])
		newret[j++] = ret[k++];
	newret[j] = '\0';
	free(ret);
	return (newret);
}

char	*add_width(char *ret, char *arg, int i, int min_width)
{
	int		zero;
	char	*newret;
	char	c;

	if (!(newret = malloc(sizeof(char) * (min_width + 3))))
		return (NULL);
	c = ' ';
	zero = 0;
	if (is_type(arg, i) == 0)
		i++;
	if (check_zero_filler(arg, i) == 1)
		zero = 1;
	if (zero == 1 && check_dash_flag(arg, i) == 0 &&
		(check_precision(arg, i) >= min_width || check_precision(arg, i) == -1))
		c = '0';
	if (check_precision(arg, i) < min_width && arg[i] == '%'
		&& check_precision(arg, i) != -1 && zero == 1)
		c = '0';
	if (check_dash_flag(arg, i) == 1)
		ret = to_dash(ret, newret, c, min_width);
	else
		ret = not_to_dash(ret, newret, c, min_width);
	return (ret);
}

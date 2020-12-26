/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:13:40 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 12:13:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*add_options(char *ret, char *arg, int i)
{
	int		min_width;
	int		precision;
	char	*newret;

	newret = NULL;
	precision = check_precision(arg, i);
	min_width = check_width(arg, i);
	if (precision < min_width && arg[i] != '%')
	{
		newret = damn_precision(ret, arg, i, precision);
		ret = newret;
	}
	if (min_width != -1 && actual_len(ret) < min_width && ((precision < 0
		|| precision < min_width) || arg[i] == 's' || arg[i + 1] == '%'))
		return (add_width(ret, arg, i, min_width));
	if (is_type(arg, i) == 1 && arg[i] != '%')
		return (damn_precision(ret, arg, i, precision));
	return (ret);
}

char	*replace_vals(char *cpyarg, int star, va_list ap, int k)
{
	int		i;
	int		j;
	char	*val;
	char	*new;

	i = 0;
	j = 0;
	val = ft_itoa(va_arg(ap, int));
	if (!(new = malloc(sizeof(char) * (ft_pstrlen(cpyarg) + ft_pstrlen(val)
	+ 1))))
		return (NULL);
	while (cpyarg[j] && j < star)
		new[i++] = cpyarg[j++];
	if (j == star)
	{
		j++;
		while (val[k])
			new[i++] = val[k++];
	}
	while (cpyarg[j])
		new[i++] = cpyarg[j++];
	new[i] = '\0';
	free(cpyarg);
	free(val);
	return (new);
}

char	*convert_type(char **cpyarg, int i, va_list ap)
{
	char *ret;

	ret = NULL;
	while (is_type(*cpyarg, i) == 0)
	{
		if ((*cpyarg)[i] == '*')
			*cpyarg = replace_vals(*cpyarg, i, ap, 0);
		i++;
	}
	if ((*cpyarg)[i] == 'c')
		ret = (convert_char(ret, ap));
	else if ((*cpyarg)[i] == 's')
		ret = (convert_str(ret, ap));
	else if ((*cpyarg)[i] == 'p')
		ret = (convert_addr(ret, ap));
	else if ((*cpyarg)[i] == 'd' || (*cpyarg)[i] == 'i')
		ret = (convert_signed_int(ret, ap));
	else if ((*cpyarg)[i] == 'u')
		ret = (convert_unsigned_int(ret, ap));
	else if ((*cpyarg)[i] == 'x' || (*cpyarg)[i] == 'X')
		ret = (convert_unsigned_hexa(ret, ap, (*cpyarg)[i]));
	else if ((*cpyarg)[i] == '%')
		ret = convert_percent(ret, &i);
	return (add_options(ret, *cpyarg, i));
}

char	**fill_tab(char **stock, char **cpyarg, va_list ap, int i)
{
	int	j;
	int k;

	j = 0;
	while ((*cpyarg)[i])
	{
		if ((*cpyarg)[i] && (*cpyarg)[i] != '%')
		{
			k = 0;
			if (!(stock[j] = malloc(sizeof(char) * (cstrlen(*cpyarg, i) + 3))))
				return (NULL);
			stock[j][k++] = 'R';
			stock[j][k++] = 1;
			while ((*cpyarg)[i] && (*cpyarg)[i] != '%')
				stock[j][k++] = (*cpyarg)[i++];
			stock[j++][k] = '\0';
		}
		if ((*cpyarg)[i] && (*cpyarg)[i] == '%')
		{
			stock[j++] = convert_type(cpyarg, ++i, ap);
			i = parse_end_format(*cpyarg, i);
		}
	}
	stock[j] = NULL;
	return (stock);
}

int		ft_printf(const char *arg, ...)
{
	va_list	ap;
	char	**stock;
	char	*cpyarg;
	int		i;

	stock = NULL;
	cpyarg = NULL;
	if (arg[0] == '\0')
		return (0);
	cpyarg = ft_strdup(arg);
	stock = init_tab(cpyarg, stock);
	va_start(ap, arg);
	i = 0;
	if (stock != NULL)
		fill_tab(stock, &cpyarg, ap, i);
	free(cpyarg);
	va_end(ap);
	return (go_print(stock));
}

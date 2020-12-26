/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_itoa.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:16:26 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 12:16:27 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*rev_tab(char *tab)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	stock;

	i = 0;
	len = ft_pstrlen(tab);
	j = len - 1;
	while (i < (ft_pstrlen(tab) / 2))
	{
		stock = tab[i];
		tab[i] = tab[j];
		tab[j] = stock;
		i++;
		j--;
	}
	tab[len] = '\0';
	return (tab);
}

static char		*init_tab_itoa(int quot, unsigned int n)
{
	char			*tab;
	int				i;
	unsigned int	j;

	j = n;
	tab = NULL;
	i = 0;
	if (!(tab = malloc(sizeof(char) * (quot + 2))))
		return (NULL);
	while (j > 9)
	{
		tab[i++] = (j % 10) + 48;
		j = j / 10;
	}
	tab[i] = j + 48;
	tab[i + 1] = '\0';
	return (rev_tab(tab));
}

char			*ft_unsigned_itoa(unsigned int n)
{
	char			*result;
	int				quot;
	unsigned int	i;

	i = n;
	quot = 0;
	while (i > 9)
	{
		quot++;
		i = i / 10;
	}
	result = init_tab_itoa(quot, n);
	return (result);
}

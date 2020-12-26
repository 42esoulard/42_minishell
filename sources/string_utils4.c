/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esoulard <esoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:19:25 by user42            #+#    #+#             */
/*   Updated: 2020/10/25 11:01:18 by esoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		one_quote(char *s, char *s1)
{
	int	i;
	int	c;

	i = (int)ft_strlen(s) + 1;
	c = 0;
	while (--i >= 0)
	{
		if (is_quote(s, i, '\"'))
			c++;
	}
	if (c != 1)
		return (0);
	c = 0;
	i = (int)ft_strlen(s1) + 1;
	while (--i >= 0)
	{
		if (is_quote(s1, i, '\"'))
			c++;
	}
	if (c != 1)
		return (0);
	return (1);
}

int		normed_char(char c)
{
	if (!c)
		return (-1);
	if (ft_isalnum(c) == 0)
		if (c != '-' && c != '_' && c != '?')
			return (-1);
	return (0);
}

int		skim_str(char *s, int k, int *i)
{
	while (s[++k] && s[k + 1])
		s[k] = s[k + 1];
	while (s[k])
		s[k++] = '\0';
	(*i)++;
	return (1);
}

int		check_var(char *sample)
{
	int		i;

	i = -1;
	if (ft_isdigit(sample[0]))
		return (-1);
	while (sample[++i])
		if (normed_char(sample[i]) == -1)
			return (-1);
	return (0);
}

int		is_separator(char *str, int i)
{
	if ((str[i] == ';' || str[i] == '|') && in_quotes(str, i) == 0)
	{
		if ((i > 0) && str[i - 1] && (str[i - 1] == '\\'))
			return (0);
		return (1);
	}
	return (0);
}

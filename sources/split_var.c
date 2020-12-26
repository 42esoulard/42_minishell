/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esoulard <esoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:19:47 by user42            #+#    #+#             */
/*   Updated: 2020/10/26 10:19:05 by esoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		count_words(char *s, char c)
{
	int i;
	int count;

	count = 0;
	i = -1;
	if (!s)
		return (count);
	while (s[0] != '\0' && is_end(s, ++i) == 0)
	{
		split_pass_quotes(s, &i);
		if (s[i] == c && !is_end(s, i + 1) && s[i + 1] != c)
			count++;
		if (is_end(s, i))
			break ;
	}
	if (s[0] != c)
		count++;
	return (count);
}

static char		**finish_him(char **result, int j, int word_count)
{
	if (j == word_count + 1)
		result[j] = NULL;
	else
	{
		if (result && result[j])
			free(result[j]);
		result[j] = NULL;
	}
	return (result);
}

static char		*newline(char **result, t_sh *sh, int *j, int *i)
{
	if (!(result[*j] = sample_str(sh, i, result[*j])))
		return (NULL);
	return (result[(*j)++]);
}

char			**ft_split_var(char *s, char c, t_sh *sh, int *i)
{
	char	**result;
	int		j;
	int		k;
	int		stock_i;

	j = 0;
	k = 0;
	if (!s || !(result = malloc(sizeof(char *) * (count_words(s, c) + 2))))
		return (NULL);
	while (is_end(s, k) == 0)
	{
		while ((is_end(s, k) == 0) && s[k] == c)
			k++;
		if ((is_end(s, k) == 0) && (stock_i = *i) >= 0)
		{
			if ((*i += k) >= 0 && (newline(result, sh, &j, i) == NULL))
				return (char_free_array(result, -1));
			k = *i - stock_i;
		}
	}
	return (finish_him(result, j, (count_words(s, c) - 1)));
}

int				is_quote_mod(char *str, int i)
{
	int count;

	count = 0;
	if (str[i] && (str[i] == '\'' || str[i] == '\"'))
	{
		if (str[i - 1] && str[i - 1] == '\\')
		{
			if (str[i] == '\'' && str[i - 1])
				if (check_single(str, i) == 1)
					return (1);
			while (--i >= 0 && str[i] && str[i] == '\\')
				count++;
			if (count % 2 != 0)
				return (0);
		}
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:13:00 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 12:13:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		count_words(char const *s, char c)
{
	int i;
	int count;

	count = 0;
	i = -1;
	while (s[0] != '\0' && s[++i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			count++;
	}
	if (s[0] != c)
		count++;
	return (count);
}

static int		count_len(char const *s, int i, char c)
{
	size_t len;

	len = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i] && s[i] != c)
	{
		len++;
		i++;
	}
	return (len);
}

static char		**finish_him(char **result, int j, int k, int word_count)
{
	if ((j == 0 && k != 0) || (j == word_count && k != 0))
		result[j + 1] = NULL;
	else
	{
		free(result[j]);
		result[j] = NULL;
	}
	return (result);
}

static char		*newline(char **result, int len, int *k, int *j)
{
	(*j)++;
	if (!(result[*j] = malloc(sizeof(char) * len)))
		return (NULL);
	*k = 0;
	return (result[*j]);
}

char			**ft_split(char const *s, char c)
{
	char	**result;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	if (!s || !(result = malloc(sizeof(char *) * (count_words(s, c) + 2))) ||
		!(result[j] = malloc(sizeof(char) * count_len(s, i, c) + 1)))
		return (NULL);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && k != 0 && result[j][0])
			if (newline(result, (count_len(s, i, c) + 1), &k, &j) == NULL)
				return (NULL);
		while (s[i] && s[i] != c)
			result[j][k++] = s[i++];
		if (k != 0)
			result[j][k] = '\0';
	}
	return (finish_him(result, j, k, (count_words(s, c) - 1)));
}

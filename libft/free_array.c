/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:08:27 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 12:08:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		free_array(char **array, int max, int ret)
{
	int i;

	if (!array)
		return (-1);
	if (max == -1)
	{
		max = 0;
		while (array[max] != NULL)
			max++;
	}
	i = -1;
	while (++i < max)
	{
		free(array[i]);
		array[i] = NULL;
	}
	free(array);
	array = NULL;
	return (ret);
}

int		free_str(char *str)
{
	if (!str)
		return (-1);
	free(str);
	str = NULL;
	return (-1);
}

int		free_two_str(char *s1, char *s2)
{
	free_str(s1);
	free_str(s2);
	return (-1);
}

int		free_array_and_str(char **arr, int max, char *str)
{
	free_array(arr, max, -1);
	free_str(str);
	return (-1);
}

char	*char_free_str(char *str)
{
	if (str)
		free(str);
	str = NULL;
	return (NULL);
}

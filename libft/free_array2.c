/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:08:35 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 12:08:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		free_two_arrays(char **arra, char **arrb)
{
	free_array(arra, -1, -1);
	free_array(arrb, -1, -1);
	return (-1);
}

int		free_two_arr_and_str(char **arra, char **arrb, char *str, int ret)
{
	free_array(arra, -1, -1);
	free_array(arrb, -1, -1);
	free_str(str);
	return (ret);
}

int		free_two_arr_two_str(char **arra, char **arrb, char *stra, char *strb)
{
	free_array(arra, -1, -1);
	free_array(arrb, -1, -1);
	free_str(stra);
	free_str(strb);
	return (-1);
}

char	**char_free_array(char **arr, int max)
{
	free_array(arr, max, -1);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:14:38 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 12:14:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstsize(t_list *lst)
{
	int count;

	if (lst)
	{
		count = 1;
		while (lst->next)
		{
			count++;
			lst = lst->next;
		}
	}
	if (!lst)
		count = 0;
	return (count);
}

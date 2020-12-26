/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:10:08 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 12:10:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *last;

	last = NULL;
	if (alst && new)
	{
		last = *alst;
		if (last != NULL)
		{
			while (last->next)
			{
				last = last->next;
			}
			last->next = new;
			new->next = NULL;
		}
		else
		{
			new->next = NULL;
			*alst = new;
		}
	}
}

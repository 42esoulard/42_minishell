/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:09:47 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 12:09:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *stock_ad;
	t_list *buf;

	buf = NULL;
	stock_ad = NULL;
	if (lst && *lst && del)
	{
		buf = *lst;
		while (buf->next != NULL)
		{
			stock_ad = buf->next;
			(*del)(buf->content);
			free(buf);
			buf = stock_ad;
		}
		if (buf->next == NULL)
		{
			(*del)(buf->content);
			free(buf);
		}
		buf = NULL;
		*lst = NULL;
	}
}

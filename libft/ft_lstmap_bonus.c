/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:11:24 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 12:11:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *newlst;
	t_list *begin;

	if (lst == NULL || !f || !del)
		return (NULL);
	if (!(newlst = ft_lstnew(NULL)))
		return (NULL);
	begin = newlst;
	while (lst)
	{
		if (!(newlst->content = (*f)(lst->content)))
		{
			ft_lstclear(&begin, del);
			return (NULL);
		}
		if (!(newlst->next = ft_lstnew(NULL)))
		{
			ft_lstclear(&begin, del);
			return (NULL);
		}
		newlst = newlst->next;
		lst = lst->next;
	}
	return (begin);
}

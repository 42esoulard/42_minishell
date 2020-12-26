/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:14:44 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 12:14:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*lstnew;

	if (!(lstnew = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (content)
	{
		if (!(lstnew->content = malloc(sizeof(content) *
			ft_strlen((char *)content) + 1)))
			return (NULL);
		ft_memcpy(lstnew->content, content, ft_strlen((char *)content) + 1);
	}
	else
		lstnew->content = NULL;
	lstnew->next = NULL;
	return (lstnew);
}

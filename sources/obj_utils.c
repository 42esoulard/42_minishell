/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esoulard <esoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:20:46 by user42            #+#    #+#             */
/*   Updated: 2020/10/21 19:25:35 by esoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** lstnew for redirection
*/

t_redir		*redir_new(void)
{
	t_redir	*new;

	if (!(new = malloc(sizeof(t_redir))))
		return (NULL);
	new->cmd_in = 0;
	new->cmd_output = 1;
	new->err_output = 2;
	return (new);
}

/*
** lstnew for object
**(same as plotted on framapad)
*/

t_obj		*obj_new(t_obj *prev)
{
	t_obj	*new;

	if (!(new = malloc(sizeof(t_obj))))
		return (NULL);
	new->obj = NULL;
	new->type = 0;
	new->option = 0;
	new->type = -1;
	new->redir = NULL;
	new->result = NULL;
	new->pip = 0;
	new->tube[0] = -1;
	new->tube[1] = -1;
	new->args = NULL;
	new->charenv = NULL;
	new->error = 0;
	new->next = NULL;
	new->prev = prev;
	new->qts = 0;
	new->fk = 0;
	return (new);
}

/*
**initialize an object, need to add potential redir (see below)
*/

char		*init_obj(t_obj *obj, char *sample, int type)
{
	if (!(obj->obj = ft_strdup(sample)))
		return (NULL);
	obj->type = type;
	return (obj->obj);
}

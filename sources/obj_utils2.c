/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:20:40 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 12:20:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		print_result(t_sh *sh, int ret, char *to_free)
{
	if (sh->obj->error)
		ft_putstr_fd(sh->obj->error, sh->obj->redir->err_output);
	else if (sh->obj->result)
		ft_putstr_fd(sh->obj->result, sh->obj->redir->cmd_output);
	free(to_free);
	return (ret);
}

void	maj_err(t_sh *sh, char *str, int err)
{
	if (!sh->obj->error)
		sh->obj->error = str;
	else if (ft_strstr(str, "Permission denied")
		&& !ft_strstr(sh->obj->error, "Permission denied"))
	{
		free(sh->obj->error);
		sh->obj->error = str;
	}
	else if (ft_strncmp(sh->obj->error, "exit\n", 5) == 0)
		sh->obj->error = ft_strjoin_bth(sh->obj->error, str);
	else
		free(str);
	g_err = err;
}

void	*free_redir(t_redir *redir)
{
	if (redir->cmd_in > 0)
		close(redir->cmd_in);
	if (redir->cmd_output != 1 && redir->cmd_output != -1)
		close(redir->cmd_output);
	if (redir->err_output != 2 && redir->err_output != -1)
		close(redir->err_output);
	free(redir);
	return (NULL);
}

int		free_obj(t_obj **obj)
{
	t_obj	*prev;

	if (!(*obj))
		return (-1);
	if (!(*obj)->prev)
		prev = NULL;
	else
		prev = (*obj)->prev;
	if ((*obj)->obj)
		free((*obj)->obj);
	free_redir((*obj)->redir);
	free((*obj)->error);
	free((*obj)->result);
	free_array((*obj)->args, -1, -1);
	free_array((*obj)->charenv, -1, -1);
	free((*obj));
	*obj = prev;
	return (-1);
}

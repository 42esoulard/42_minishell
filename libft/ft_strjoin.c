/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:12:32 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 12:12:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

char		*ft_printf_strjoin(char *s1, char *s2, int stocklen, int ratlen)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(new = malloc(sizeof(char) * (ratlen + stocklen + 1))))
		return (NULL);
	while (i < ratlen)
	{
		new[i] = s1[i];
		i++;
	}
	while (j < stocklen)
		new[i++] = s2[j++];
	new[i] = '\0';
	free(s1);
	free(s2);
	return (new);
}

char		*ft_strjoin_sp(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	i = -1;
	j = 0;
	new = NULL;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	while (s2[j])
		j++;
	if (!(new = malloc(sizeof(char) * (ft_pstrlen(s1) + j + 2))))
		return (NULL);
	while (s1[++i])
		new[i] = s1[i];
	j = 0;
	if (ft_pstrlen(s1) > 0)
		new[i++] = ' ';
	while (s2[j])
		new[i++] = s2[j++];
	new[i] = '\0';
	free_two_str(s1, s2);
	return (new);
}

char		*ft_strjoin_bth(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	i = -1;
	j = 0;
	new = NULL;
	if ((s1 == NULL || s2 == NULL) && (free_two_str(s1, s2) == -1))
		return (NULL);
	while (s2[j])
		j++;
	if (!(new = malloc(sizeof(char) * (ft_pstrlen(s1) + j + 1))))
		return (NULL);
	while (s1[++i])
		new[i] = s1[i];
	j = 0;
	while (s2[j])
		new[i++] = s2[j++];
	new[i] = '\0';
	free(s1);
	s1 = NULL;
	free(s2);
	s2 = NULL;
	return (new);
}

char		*ft_strjoin_dic(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	i = -1;
	j = 0;
	new = NULL;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	while (s2[j])
		j++;
	if (!(new = malloc(sizeof(char) * (ft_pstrlen(s1) + j + 2))))
		return (NULL);
	while (s1[++i])
		new[i] = s1[i];
	j = 0;
	new[i++] = '=';
	while (s2[j])
		new[i++] = s2[j++];
	new[i] = '\0';
	return (new);
}

char		*ft_strjoin_slash(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	i = -1;
	j = 0;
	new = NULL;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	while (s2[j])
		j++;
	if (!(new = malloc(sizeof(char) * (ft_pstrlen(s1) + j + 2))))
		return (NULL);
	while (s1[++i])
		new[i] = s1[i];
	j = 0;
	new[i++] = '/';
	while (s2[j])
		new[i++] = s2[j++];
	new[i] = '\0';
	return (new);
}

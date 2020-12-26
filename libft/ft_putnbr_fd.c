/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:13:17 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 12:13:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	i;
	int		div;
	long	o;

	div = 1;
	o = n;
	if (fd >= 0)
	{
		if (o < 0)
		{
			write(fd, "-", 1);
			o *= -1;
		}
		while ((o / div) > 9)
			div *= 10;
		while (div > 1)
		{
			i = ((o / div) % 10) + 48;
			write(fd, &i, 1);
			div /= 10;
		}
		i = (o % 10) + 48;
		write(fd, &i, 1);
	}
}

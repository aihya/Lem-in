/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 16:00:31 by aihya             #+#    #+#             */
/*   Updated: 2019/12/22 17:00:12 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr_fd(char const *c, int fd)
{
	unsigned int	i;

	if (c)
	{
		i = 0;
		while (c[i])
		{
			write(fd, &c[i], 1);
			i++;
		}
	}
}

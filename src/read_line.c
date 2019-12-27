/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 12:00:24 by aihya             #+#    #+#             */
/*   Updated: 2019/12/27 12:20:35 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

char	*read_line(void)
{
	char	*line;
	char	buff[1];
	char	buffer[1024];
	int		ret;
	int		i;

	buff[0] = '\0';
	line = NULL;
	ret = 0;
	i = 0;
	while ((ret = read(STDIN_FILENO, buff, 1)) != -1 && i < 1023)
	{
		if (ft_strchr(buff, '\n') || ret == 0)
			break ;
		buffer[i] = buff[0];
		ret = 0;
		i++;
	}
	buffer[i] = 0;
	line = ft_strdup(buffer);
	return (line);
}

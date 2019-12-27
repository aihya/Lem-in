/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoumi <magoumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 11:58:57 by aihya             #+#    #+#             */
/*   Updated: 2019/12/27 19:17:29 by magoumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int     read_content(t_data *data)
{
	char	*line;
	int		ret;

	data->content = NULL;
	ret = -1;
	while ((ret = get_next_line(STDOUT, &line)) == 1)
	{	
		ft_chain_push(&(data->content),line);
		ft_strdel(&line);
	}
	if (ret == -1)
		return (0);
	return (1);
}

int		read_all(t_data *data)
{
	if (!read_content(data))
		return (0);
	if (data->content == NULL)
		return (0);
	if ((data->na = ft_atoi(data->content[0])) <= 0)
		return (0);
	printf("ants num [%d]\n", data->na);
	return (1);
}

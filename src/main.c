/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 21:35:34 by aihya             #+#    #+#             */
/*   Updated: 2020/01/02 16:19:30 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		error()
{
	ft_putendl("ERROR");
	return (0);
}

int		main(void)
{
	t_data		data;
	t_vertex*	room;
	int		i;

	data.na = 0;
	data.nr = 0;
	data.is = -1;
	data.ie = -1;
	data.start = NULL;
	data.end = NULL;
	data.content = NULL;
//	ft_putendl("-------------- 0\n");
	if (!read_content(&data))
		return (error());
//	ft_putendl("-------------- 1\n");
	if (data.nr == 0)
		return (error());
//	ft_putendl("-------------- 2\n");
	init_hashtable(&data);
//	ft_putendl("-------------- 3\n");
	if (fill_hashtable(&data) == 0)
		return (error());
//	ft_putendl("-------------- 4\n");
	i = 0;
	while (i < data.nr)
	{
		printf("%d:\n", i);
		room = data.hashtable[i];
		while (room)
		{
			printf("\t%s\n", room->name);
			room = room->next;
		}
		i++;
	}
}

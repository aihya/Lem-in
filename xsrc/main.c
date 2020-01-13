/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 21:35:34 by aihya             #+#    #+#             */
/*   Updated: 2020/01/13 15:08:07 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		error(char *from)
{
	ft_putstr("ERROR: ");
	ft_putendl(from);
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
	if (!read_content(&data))
		return (error("read_content"));
	if (data.nr == 0)
		return (error("data.nr"));
	if (init_hashtable(&data) == 0)
		return (error("init_hashtable"));
	if (fill_hashtable(&data) == 0)
		return (error("fill_hashtable"));
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
	return (0);
}

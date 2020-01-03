/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 21:35:34 by aihya             #+#    #+#             */
/*   Updated: 2020/01/03 15:49:09 by aihya            ###   ########.fr       */
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
	if (!read_content(&data))
		return (error());
	if (data.nr == 0)
		return (error());
	if (init_hashtable(&data) == 0)
		return (error());
	if (fill_hashtable(&data) == 0)
		return (error());
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

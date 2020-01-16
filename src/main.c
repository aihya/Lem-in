/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 21:35:34 by aihya             #+#    #+#             */
/*   Updated: 2020/01/16 22:30:38 by aihya            ###   ########.fr       */
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
	t_link*		link;
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
	if (parse_links(&data) == 0)
		return (error("parse_links"));
	i = 0;
	while (i < data.nr)
	{
		printf("%d:\n", i);
		room = data.hashtable[i];
		while (room)
		{
			ft_putchar('\t');
			ft_putstr(room->name);
			ft_putchar(':');
			link = room->links;
			while (link)
			{
				ft_putchar(' ');
				ft_putstr(link->dest->name);
				link = link->next;
			}
			room = room->next;
			ft_putchar('\n');
		}
		ft_putchar('\n');
		i++;
	}
	return (0);
}

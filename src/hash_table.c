/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 12:18:29 by aihya             #+#    #+#             */
/*   Updated: 2019/12/30 20:20:38 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		init_hashtable(t_data* data)
{
	int		i;
	int		nr;

	nr = data->nr;
	if ((data->hashtable = (t_room**)malloc(sizeof(t_room*) * nr)) == NULL)
		return (0);
	i = 0;
	while (i < nr)
	{
		data->hashtable[i] = NULL;
		i++;
	}
	return (1);
}

t_room*	new_room(char* name)
{
	t_room*	room;

	if ((room = (t_room*)malloc(sizeof(t_room))) == NULL)
		return (NULL);
	room->name = ft_strdup(name);
	room->next = NULL;
	return (room);
}

int		hash_function(char *str, int upper_bound)
{
	int		hash;
	int		i;
	int		len;

	len = ft_strlen(str);
	hash = 0;
	i = 0;
	while (str[i])
	{
		hash += str[i] * len;
		i++;
	}
	hash = hash % upper_bound;
	return (hash);
}

t_room*	add_to_hashtable(t_data *data, int hash, char *value)
{
	t_room	*room;

	if (data->hashtable[hash] == NULL)
	{
		if ((data->hashtable[hash] = new_room(value)) == NULL)
			return (NULL);
		return (data->hashtable[hash]);
	}
	room = data->hashtable[hash];
	while (room->next)
	{
		if (ft_strequ(room->name, value))
			return (NULL);
		room = room->next;
	}
	if (ft_strequ(room->name, value))
		return (NULL);
	if ((room->next = new_room(value)) == NULL)
		return (NULL);
	return (room->next);
}

int		fill_hashtable(t_data* data)
{
	int		i;
	int		hash;
	char**	buff;
	t_room*	room;

	if (data->content == NULL)
		return (0);
	i = 0;
	while (data->content[i])
	{
		if (is_room(data->content[i]))
		{
			buff = ft_strsplit(data->content[i], ' ');
			if (buff == NULL)
				return (0);
			hash = hash_function(buff[0], data->nr);
			if ((room = add_to_hashtable(data, hash, buff[0])) == NULL)
				return (0);
			ft_chain_free(&buff);
			if (i - 1 >= 0 && ft_strequ(data->content[i - 1], START_CMD))
			{
				data->is = hash;
				data->start = room;
			}
			if (i - 1 >= 0 && ft_strequ(data->content[i - 1], END_CMD))
			{
				data->ie = hash;
				data->end = room;
			}
		}
		i++;
	}
	return (1);
}

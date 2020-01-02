/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 12:18:29 by aihya             #+#    #+#             */
/*   Updated: 2020/01/02 16:25:15 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		init_hashtable(t_data* data)
{
	int		i;
	int		nr;

	nr = data->nr;
	if ((data->hashtable = (t_vertex**)malloc(sizeof(t_vertex*) * nr)) == NULL)
		return (0);
	i = 0;
	while (i < nr)
	{
		data->hashtable[i] = NULL;
		i++;
	}
	return (1);
}

t_vertex*	new_vertex(char* name)
{
	t_vertex*	vertex;

	if ((vertex = (t_vertex*)malloc(sizeof(t_vertex))) == NULL)
		return (NULL);
	vertex->name = ft_strdup(name);
	vertex->next = NULL;
	return (vertex);
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

t_vertex*	add_to_hashtable(t_data *data, int hash, char *value)
{
	t_vertex	*vertex;

	if (data->hashtable[hash] == NULL)
	{
		if ((data->hashtable[hash] = new_vertex(value)) == NULL)
			return (NULL);
		return (data->hashtable[hash]);
	}
	vertex = data->hashtable[hash];
	while (vertex->next)
	{
		if (ft_strequ(vertex->name, value))
			return (NULL);
		vertex = vertex->next;
	}
	if (ft_strequ(vertex->name, value))
		return (NULL);
	if ((vertex->next = new_vertex(value)) == NULL)
		return (NULL);
	return (vertex->next);
}

int		fill_hashtable(t_data* data)
{
	int		i;
	int		hash;
	char**	buff;
	t_vertex*	vertex;

	if (data->content == NULL)
		return (0);
	i = 0;
	while (data->content[i])
	{
//		if (ft_strequ(data->content[i], START_CMD))
//		{
//			if (data->content[i + 1] && !is_vertex(data->content[i]))
//		}
		if (is_vertex(data->content[i]))
		{
			buff = ft_strsplit(data->content[i], ' ');
			if (buff == NULL)
				return (0);
			hash = hash_function(buff[0], data->nr);
			if ((vertex = add_to_hashtable(data, hash, buff[0])) == NULL)
				return (0);
			ft_chain_free(&buff);
			if (i - 1 >= 0 && ft_strequ(data->content[i - 1], START_CMD))
			{
				data->is = hash;
				data->start = vertex;
			}
			if (i - 1 >= 0 && ft_strequ(data->content[i - 1], END_CMD))
			{
				data->ie = hash;
				data->end = vertex;
			}
		}
		i++;
	}
	if (data->start == NULL || data->end == NULL)
		return (0);
	return (1);
}

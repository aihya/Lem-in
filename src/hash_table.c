/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 12:18:29 by aihya             #+#    #+#             */
/*   Updated: 2020/01/03 19:02:12 by aihya            ###   ########.fr       */
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

t_vertex*	set_vertex(t_data* data, int index, int* hash)
{
	char**		buff;
	t_vertex*	vertex;
	int			_hash;

	vertex = NULL;
	if ((buff = ft_strsplit(data->content[index], ' ')) == NULL)
		return (NULL);
	_hash = hash_function(buff[0], data->nr);
	if ((vertex = add_to_hashtable(data, _hash, buff[0])) == NULL)
		return (NULL);
	if (hash)
		*hash = _hash;
	ft_chain_free(&buff);
	return (vertex);
}

int		duplicate(char* command)
{
	static int	start = 0;
	static int	end = 0;

	if (ft_strequ(command, START_CMD))
	{
		if (++start != 1)
			return (1);
	}
	else if (ft_strequ(command, END_CMD))
	{
		if (++end != 1)
			return (1);
	}
	return (0);
}

int		set_command(t_data* data, int index)
{
	int			hash;

	if (duplicate(data->content[index]))
		return (0);
	hash = 0;
	if (data->content[index + 1])
	{
	printf("--> [%s]\n", data->content[index + 1]);
		if (is_vertex(data->content[index + 1]) != 1)
			return (0);
		if (ft_strequ(data->content[index], START_CMD))
		{
			if ((data->start = set_vertex(data, index + 1, &hash)) == NULL)
				return (0);
			data->is = hash;
		}
		else
		{
			if ((data->end = set_vertex(data, index + 1, &hash)) == NULL)
				return (0);
			data->ie = hash;
		}
		return (1);
	}
	return (0);
}

int		fill_hashtable(t_data* data)
{
	int			i;
//	int			hash;
//	char**		buff;
//	t_vertex*	vertex;

	if (data->content == NULL)
		return (0);
	i = 0;
	while (data->content[i])
	{
		if (ft_strequ(data->content[i], START_CMD)
		||	ft_strequ(data->content[i], END_CMD))
		{
			if (!set_command(data, i))
				return (0);
			i++;
		}
		else if (is_vertex(data->content[i]) && set_vertex(data, i, NULL) == NULL)
			return (0);
//		{
//			buff = ft_strsplit(data->content[i], ' ');
//			if (buff == NULL)
//				return (0);
//			hash = hash_function(buff[0], data->nr);
//			if ((vertex = add_to_hashtable(data, hash, buff[0])) == NULL)
//				return (0);
//			ft_chain_free(&buff);
//		}
		i++;
	}
	if (data->start == NULL || data->end == NULL)
		return (0);
	return (1);
}

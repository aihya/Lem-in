/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 19:01:47 by aihya             #+#    #+#             */
/*   Updated: 2020/01/16 22:44:12 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

/*
	Checks whether the vertex exist in the data.hashtable.
	returns the address of the vertex when found.
	returns NULL otherwise.
*/
t_vertex	*get_vertex(t_data *data, char *name)
{
	int			hash;
	t_vertex	*curr;

	hash = hash_function(name, data->nr);
	curr = data->hashtable[hash];
	while (curr)
	{
		if (ft_strequ(curr->name, name))
			break ;
		curr = curr->next;
	}
	return (curr);
}

/*
	Checks if all parts of link exist on the hashtable.
	returns 1 on success.
	returns 0 otherwise.
*/
int			check_link(t_data *data, int index)
{
	char	**buff;
	int		ret;

	buff = NULL;
	ret = 1;
	if (ret && (buff = ft_strsplit(data->content[index], '-')) == NULL)
		ret = 0;
	if (ret && !get_vertex(data, buff[0]))
		ret = 0;
	if (ret && !get_vertex(data, buff[1]))
		ret = 0;
	ft_chain_free(&buff);
	return (ret);
}

/*
	Allocate memory for a new link and return it's address.
*/
t_link		*new_link(t_vertex *dest)
{
	t_link	*link;

	if ((link = (t_link *)malloc(sizeof(t_link))) == NULL)
		return (NULL);
	link->flow = 0;
	link->dest = dest;
	link->next = NULL;
	return (link);
}

/*
	Attempts to push the vertex with the name "dest_name", 
	to the end of linked list "links" of the vertex "trgt_name".
	returns 0 if the allocation of the new link failed.
	returns 1 otherwise.
*/
int			push_link(t_data *data, char *trgt_name, char *dest_name)
{
	t_vertex	*trgt_addr;
	t_link		*curr;

	trgt_addr = get_vertex(data, trgt_name);
	curr = trgt_addr->links;
	while (curr)
	{
		if (ft_strequ(curr->dest->name, dest_name))
			return (1);
		if (curr->next == NULL)
			break ;
		curr = curr->next;
	}
	if (curr)
	{
		if ((curr->next = new_link(get_vertex(data, dest_name))) == NULL)
			return (0);
		trgt_addr->counter++;
		return (1);
	}
	if ((trgt_addr->links = new_link(get_vertex(data, dest_name))) == NULL)
		return (0);
	trgt_addr->counter++;
	return (1);
}

/*
	Wire two vertices using the logic of the function "push_link".
	The wiring goes in both directions.
*/
int			wire_vertices(t_data *data, int index)
{
	char		**buff;
	int			ret;

	ret = 1;
	buff = NULL;
	if ((buff = ft_strsplit(data->content[index], '-')) == NULL)
		ret = 0;
	if (ret && push_link(data, buff[0], buff[1]) == 0)
		ret = 0;
	if (ret && push_link(data, buff[1], buff[0]) == 0)
		ret = 0;
	ft_chain_free(&buff);
	return (1);
}

/*
	Attempts to wire two vertices using the logic of function "wire_vertices", 
	after checking that both vertices already exist in data.hashtable.
*/
int			parse_links(t_data *data)
{
	int		i;

	i = data->last_index;
	if (data->content[i] == NULL)
		return (0);
	while (data->content[i])
	{
		if (is_comment(data->content[i]) && ++i)
			continue ;
		if (check_link(data, i) == 0)
			return (0);
		if (wire_vertices(data, i) == 0)
			return (0);
		i++;
	}
	return (1);
}

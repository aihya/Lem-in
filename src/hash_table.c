/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 12:18:29 by aihya             #+#    #+#             */
/*   Updated: 2019/12/27 17:37:55 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		init_hash_table(t_data* data, int n)
{
	int		i;

	if ((data->hashtable = (t_room**)malloc(sizeof(t_room*) * n)) == NULL)
		return (0);
	i = 0;
	while (i < n)
	{
		data->hashtable[i] = NULL;
		i++;
	}
	return (1);
}



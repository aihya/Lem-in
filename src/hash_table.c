/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 12:18:29 by aihya             #+#    #+#             */
/*   Updated: 2019/12/27 20:29:01 by aihya            ###   ########.fr       */
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

//int		fill_hashtable(t_data *data)
//{
//	int		i;
//	int		**buff;
//
//	if (data->content == NULL)
//		return (0);
//	i = 0;
//	while (data->content[i])
//	{
//		buff = ft_strsplit_del(data->content[i], "-");
//		if (ft_chain_size(buff) != 2)
//		{
//			ft_chain_free(&buff);
//			return (0);
//		}
//		i++;
//	}
//}

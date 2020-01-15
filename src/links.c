/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 19:01:47 by aihya             #+#    #+#             */
/*   Updated: 2020/01/15 19:50:55 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		parse_link(t_data *data, int index)
{
	
}

int		parse_links(t_data *data)
{
	int		i;

	i = data->last_index;
	while (data->content[i])
	{
		if (is_comment(data->content[i]) && ++i)
			continue ;
		
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 21:36:40 by aihya             #+#    #+#             */
/*   Updated: 2019/12/27 16:23:28 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdio.h>
# include <stdlib.h>


typedef	struct	s_room
{
	char*		name;
	t_room*		relatives;
	t_room*		ht_next;
}				t_room;

typedef	struct	s_data
{
	int			n;
	t_room**	hashtable;
}				t_data;

int		init_hash_table(t_data* data, int n);

#endif

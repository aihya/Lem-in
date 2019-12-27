/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoumi <magoumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 21:36:40 by aihya             #+#    #+#             */
/*   Updated: 2019/12/27 16:27:10 by magoumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdio.h>
# include <stdlib.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_lst
{
	char			*cut;
	int				fd;
	struct s_lst	*next;
}					t_lst;

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

char*	read_line(void);
int		init_hash_table(t_data* data, int n);

#endif

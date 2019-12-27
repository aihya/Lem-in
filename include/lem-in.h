/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoumi <magoumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 21:36:40 by aihya             #+#    #+#             */
/*   Updated: 2019/12/27 17:56:16 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdio.h>
# include <stdlib.h>
# include "libft.h"

typedef	struct	s_room
{
	char*			name;
	struct s_room*	relatives;
	struct s_room*	next;
}				t_room;

typedef	struct	s_data
{
	int				na;
	int				nr;
	int				is;
	int				ie;
	char			**content;
	t_room			*rooms;
	t_room**		hashtable;
}				t_data;

int	get_next_line(const int fd, char **line);
int	init_hashtable(t_data* data);

#endif

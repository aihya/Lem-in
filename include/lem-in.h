/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 21:36:40 by aihya             #+#    #+#             */
/*   Updated: 2020/01/03 23:51:18 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

# define START_CMD	"##start"
# define END_CMD	"##end"
# define CMD		1
# define COMMENT	2
# define VERTEX		1
# define LINK		2

typedef	struct	s_vertex
{
	char*				name;
	struct s_vertex*	neighbors;
	struct s_vertex*	next;
}				t_vertex;

typedef	struct	s_data
{
	int				na;
	int				nr;
	int				is;
	int				ie;
	char**			content;
	t_vertex*		vertices;
	t_vertex*		start;
	t_vertex*		end;
	t_vertex**		hashtable;
}				t_data;

int				get_next_line(const int fd, char** line);
int				init_hashtable(t_data* data);
int				read_content(t_data* data);
int				is_vertex(char *line);
int				init_hashtable(t_data* data);
int				fill_hashtable(t_data* data);
int				error();

#endif

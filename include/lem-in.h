/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 21:36:40 by aihya             #+#    #+#             */
/*   Updated: 2020/01/16 22:14:32 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"

# define START_CMD	"##start"
# define END_CMD	"##end"
# define CMD		1
# define COMMENT	2
# define VERTEX		1
# define LINK		2

typedef struct	s_link
{
	int				flow;
	struct s_vertex	*dest;
	struct s_link	*next;
}				t_link;

typedef	struct	s_vertex
{
	char			*name;
	unsigned int	counter;
	struct s_link	*links;
	struct s_vertex	*next;
}				t_vertex;

typedef	struct	s_data
{
	int				last_index;
	int				na;
	int				nr;
	int				is;
	int				ie;
	char			**content;
	t_vertex		*vertices;
	t_vertex		*start;
	t_vertex		*end;
	t_vertex		**hashtable;
}				t_data;

int				read_content(t_data *data);
int				is_vertex(char *line);
int				is_comment(char* line);
int				init_hashtable(t_data *data);
int				fill_hashtable(t_data *data);
int				hash_function(char *str, int upper_bound);
int				parse_links(t_data *data);
int				error();

#endif

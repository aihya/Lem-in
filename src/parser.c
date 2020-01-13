/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 15:49:03 by aihya             #+#    #+#             */
/*   Updated: 2020/01/13 17:09:43 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

char*	read_line()
{
	int		ret;
	char*	line;
	char	buff[2];

	line = NULL;
	ret = 0;
	while ((ret = read(STDIN_FILENO, buff, 1)) != -1)
	{
		buff[1] = '\0';
		if (buff[0] == '\n' || ret == 0)
			break ;
		ft_strojoin(&line, buff, 1);
		ret = 0;
	}
	return (line);
}

int		comment_type(char *line)
{
	if (line[0] == '#')
	{
		if (ft_strequ(line, START_CMD) || ft_strequ(line, END_CMD))
			return (CMD);
		return (CMT);
	}
	return (0);
}

int		append_line(t_data* data, char* line, int* v_flag)
{
	int		type;

	if (comment_type(line) != 0)
	{
		ft_chain_push(&(data->content), line)
		return (1);
	}
	type = line_type(line);
	if (type == VERTEX && *v_flag == 1)
	{
		data->nr++;
		ft_chain_push(&(data->content), line);
		return (1);
	}
	else if (type == VERTEX && *v_flag == 0)
		return (0);
	if (type == LINK && )
}



int		read_content(t_data* data)
{
	char*	line;
	int		first_line;
	int		v_flag;

	v_flag = 1;
	first_line = 1;
	line = NULL;
	while ((line = read_line()) != NULL)
	{
		if (ft_strlen(line) == 0)
			return (0);
		if (ft_strisempty(line))
			return (0);
		if (first_line)
		{
			if (comment_type(line) == CMT)
				continue ;
			if (!ft_strisnum(line) || (data->na = ft_atoi(line)) <= 0)
				return (0);
			first_line = 0;
			continue ;
		}
		if (!append_line(data, line, &v_flag))
			return (0);
	}
	return (1);
}

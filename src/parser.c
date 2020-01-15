/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 19:08:29 by aihya             #+#    #+#             */
/*   Updated: 2020/01/15 18:23:19 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

char	*read_line(void)
{
	char	*line;
	char	buff[2];
	int		ret;

	line = NULL;
	ret = 0;
	while ((ret = read(0, buff, 1)) != -1)
	{
		if (buff[0] == '\n' || ret == 0)
			break ;
		buff[1] = '\0';
		ft_strojoin(&line, buff, 1);
		ret = 0;
	}
	return (line);
}

/*
	returns 1 when the line corresponds to a start or end command.
	returns 2 when it a comment.
	otherwise, returns 0.
*/
int		comment_type(char *line)
{
	if (line[0] == '#')
	{
		if (ft_strequ(line, START_CMD) || ft_strequ(line, END_CMD))
			return (1);
		return (2);
	}
	return (0);
}

/*
	Check if the line corresponds to a comment in general
	and push to data.content buffer for later parsing.
*/
int		is_comment(char* line)
{
	int		type;

	type = comment_type(line);
	if (type == CMD || type == COMMENT)
		return (1);
	return (0);
}

/*
	Checks whether the line corresponds to a vertex in the following form:
		NAME X_COORD Y_COORD
	if the line contains invalid caracters, the function -1 as a response.
*/
int		is_vertex(char* line)
{
	int		i;
	int		ret;
	char**	buf;

	i = 0;
	while (line[i])
	{
		if (!ft_isprint(line[i]) && line[i] != ' ')
			return (0);
		i++;
	}
	ret = 1;
	if (ft_char_count(line, ' ') != 2)
		return (0);
	buf = ft_strsplit(line, ' ');
	if (ft_chain_size(buf) != 3 || !ft_strisnum(buf[1]) || !ft_strisnum(buf[2]))
		ret = 0;
	if (ret == 1 && (ft_strchr(buf[0], '-') || buf[0][0] == 'L'))
		ret = 0;
	ft_chain_free(&buf);
	return (ret);
}

int		is_link(char* line)
{
	int		i;
	int		ret;
	char**	buf;

	i = 0;
	while (line[i])
	{
		if (!ft_isprint(line[i]) || line[i] == ' ')
			return (0);
		i++;
	}
	ret = 1;
	if (ft_char_count(line, '-') != 1)
		ret = 0;
	if (ret && (buf = ft_strsplit(line, '-')) == NULL)
		ret = 0;
	if (ret && ft_chain_size(buf) != 2)
		ret = 0;
	ft_chain_free(&buf);
	return (ret);
}

/*
	Checks whether the line is a vertex or a line(edge).
	returns the macro VERTEX or LINK if it corresponds to a vertex or line.
	if it has invalid caracters, return -1 as a signal.
*/
int		check_line(char* line)
{
	int		ret;

	ret = 0;
	if ((ret = is_vertex(line)) == 1)
		return (VERTEX);
	else if ((ret = is_link(line)) == 1)
		return (LINK);
	return (0);
}

/*
	Attempts to append the line to data.content buffer only if it is a vertex
	or a link(edge) or a comment(including commands).
	otherwise, return 0 as an error signal.
*/
int		append_line(t_data* data, char* line, int* v_flag, int* init_stat)
{
	int		type;

	if (is_comment(line))
	{
		ft_chain_push(&(data->content), line);
		return (1);
	}
	type = check_line(line);
	if (type == VERTEX && *v_flag == 1 && !(*init_stat = 0))
	{
		data->nr++;
		ft_chain_push(&(data->content), line);
		return (1);
	}
	else if (type == VERTEX && *v_flag == 0)
		return (0);
	if (type == LINK && *init_stat == 1)
		return (0);
	else if (type == LINK && !(*v_flag = 0))
	{
		ft_chain_push(&(data->content), line);
		return (1);
	}
	return (0);
}

int		read_content(t_data *data)
{
	int		test_first_line;
	char*	line;
	int		v_flag;
	int		init_stat;

	v_flag = 1;
	init_stat = 1;
	line = NULL;
	test_first_line = 1;
	while ((line = read_line()))
	{
		if (ft_strlen(line) == 0)
			return (0);
		if (ft_strisempty(line))
			return (0);
		if (comment_type(line) == COMMENT)
			continue ;
		if (test_first_line)
		{
			if (!ft_strisnum(line) || (data->na = ft_atoi(line)) <= 0)
				return (0);
			test_first_line = 0;
		}
		else if (!append_line(data, line, &v_flag, &init_stat))
			return (0);
		ft_strdel(&line);
	}
	return (1);
}

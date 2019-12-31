/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 19:08:29 by aihya             #+#    #+#             */
/*   Updated: 2019/12/31 19:00:20 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		is_comment(char *line)
{
	if (line[0] == '#')
	{
		if (ft_strequ(line, START_CMD) || ft_strequ(line, END_CMD))
			return (1);
		return (2);
	}
	return (0);
}

int		comment_check(t_data* data, char* line)
{
	int		status;

	status = is_comment(line);
	if (status == CMD)
		ft_chain_push(&(data->content), line);
	return (status);
}

int		is_room(char* line)
{
	int		i;
	int		ret;
	char**	buf;

	i = 0;
	while (line[i])
	{
		if (!ft_isprint(line[i]) && line[i] != ' ')
			return (-1);
		i++;
	}
	ret = 1;
	if (ft_char_count(line, ' ') != 2)
		return (0);
	buf = ft_strsplit(line, ' ');
	if (ft_chain_size(buf) != 3 || !ft_strisnum(buf[1]) || !ft_strisnum(buf[2]))
		ret = 0;
	if (ret == 1 && (ft_strchr(buf[0], '-') || buf[0][0] == 'L'))
		ret = -1;
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
		if (!ft_isprint(line[i]))
			return (-1);
		i++;
	}
	ret = 1;
	if (ft_char_count(line, '-') != 1)
		return (0);
	buf = ft_strsplit(line, '-');
	if (ft_chain_size(buf) != 2)
		ret = 0;
	return (1);
}

int		check_line(char* line)
{
	int		ret;

	ret = 0;
	if ((ret = is_room(line)) == 1)
		return (ROOM);
	else if (ret == -1)
		return (-1);
	if ((ret = is_link(line)) == 1)
		return (LINK);
	else if (ret == -1)
		return (-1);
	return (0);
}

int		append_line(t_data* data, char* line)
{
	static int	init_stat = 1;
	static int	room_flag = 1;
	int			type;

	if (comment_check(data, line) == 1)
		return (1);
	type = check_line(line);
	if (type == ROOM && room_flag == 1 && !(init_stat = 0))
	{
		ft_chain_push(&(data->content), line);
		return (1);
	}
	else if (type == ROOM && room_flag == 0)
		return (0);
	if (type == LINK && init_stat == 1)
		return (0);
	else if (type == LINK && !(room_flag = 0))
	{
		ft_chain_push(&(data->content), line);
		return (1);
	}
	return (0);
}

int		read_content(t_data *data)
{
	int		ret;
	int		test_first_line;
	char*	line;

	ret = 0;
	line = NULL;
	test_first_line = 1;
	while ((ret = get_next_line(STDIN_FILENO, &line)) == 1)
	{
		printf("LINE: [%s]\n", line);
		if (!ft_strisempty(line))
			return (0);
		if (test_first_line)
		{
			if (!ft_strisnum(line) || (data->na = ft_atoi(line)) <= 0)
				return (0);
		}
		if (!append_line(data, line))
			return (0);
		printf("LINEEE\n");
		ft_strdel(&line);
	}
	if (ret == -1)
		return (0);
	return (1);
}
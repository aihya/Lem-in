/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 19:08:29 by aihya             #+#    #+#             */
/*   Updated: 2019/12/30 20:19:48 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		is_comment(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (!ft_isprint(line[i]))
			return (-1);
		i++;
	}
	if (line[0] == '#')
	{
		if (ft_strequ(line, START_CMD) || ft_strequ(line, END_CMD))
			return (1);
		return (2);
	}
	return (0);
}

int		check_line(char* line)
{
	int		type;

	type = 0;
	if ((type = is_room(line)) == 1)
		return (ROOM);
	if (type == -1)
		return (-1);
	if ((type = is_link(line)) == 1)
		return (LINK);
	if (type == -1)
		return (-1);
	return (0);
}

int		append_line(t_data* data, char* line)
{
	static int	init_stat = 1;
	static int	room_flag = 1;
	static int	link_flag = 0;
	int			status;

	status = 0;
	if ((status = is_comment(line)) == -1)
		return (0);
	else if (status == CMD)
	{
		ft_chain_push(&(data->content), line);
		return (1);
	}
	else if (status == COMMENT)
		return (1);

	status = check_line(line);
	if (room_flag == 1)
	{
		if (status == LINK && init_stat == 1 && !(init_stat = 0))
			return (0);
		else if (status == LINK)
		{
			room_flag = 0;
			link_flag = 1;
		}
		if (status == ROOM && ++(data->nr))
		{
			ft_chain_push(&(data->content), line);
			return (1);
		}
	}
	if (link_flag == 1)
	{
		if (status == ROOM)
			return (0);
		else if (status == LINK)
		{
			ft_chain_push(&(data->content), line);
			return (1);
		}
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
		if (!ft_strisempty(line))
			return (0);
		if (test_first_line)
		{
			if (!ft_strisnum(line))
				return (0);
			if ((data->na = ft_atoi(line)) <= 0)
				return (0);
		}
		if (!append_line(data, line))
			return (0);
	}
	if (ret == -1)
		return (0);
	return (1);
}
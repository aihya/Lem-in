/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 19:08:29 by aihya             #+#    #+#             */
/*   Updated: 2020/01/03 23:43:32 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

char	*read_line(void)
{
	char	*line;
	char	buff;
	char	buffer[1024];
	int		ret;
	int		i;

	buff = '\0';
	buffer[0] = '\0';
	line = NULL;
	ret = 0;
	i = 0;
	while ((ret = read(STDIN_FILENO, &buff, 1)) != -1 && i < 1024)
	{
		if (buff == '\n' || ret == 0)
			break ;
		buffer[i] = buff;
		ret = 0;
		i++;
	}
	buffer[i] = '\0';
	if (i == 0)
		return (NULL);
	line = ft_strdup(buffer);
	return (line);
}

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
	if (status == CMD || status == COMMENT)
	{
		ft_chain_push(&(data->content), line);
		return (1);
	}
	return (0);
}

int		is_vertex(char* line)
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
		if (!ft_isprint(line[i]) || line[i] == ' ')
			return (-1);
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

int		check_line(char* line)
{
	int		ret;

	ret = 0;
	if ((ret = is_vertex(line)) == 1)
		return (VERTEX);
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
	static int	vertex_flag = 1;
	int			type;

	if (comment_check(data, line) == 1)
		return (1);
	type = check_line(line);
	if (type == VERTEX && vertex_flag == 1 && !(init_stat = 0))
	{
		data->nr++;
		ft_chain_push(&(data->content), line);
		return (1);
	}
	else if (type == VERTEX && vertex_flag == 0)
		return (0);
	if (type == LINK && init_stat == 1)
		return (0);
	else if (type == LINK && !(vertex_flag = 0))
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

	line = NULL;
	test_first_line = 1;
	while ((line = read_line()))
	{
		ft_putendl(line);
		if (ft_strlen(line) == 0)
			return (0);
		if (ft_strisempty(line))
			return (0);
		if (test_first_line)
		{
			if (!ft_strisnum(line) || (data->na = ft_atoi(line)) <= 0)
				return (0);
			test_first_line = 0;
			continue ;
		}
		if (!append_line(data, line))
			return (0);
		ft_strdel(&line);
	}
	return (1);
}

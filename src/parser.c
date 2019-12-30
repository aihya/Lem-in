/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 11:58:57 by aihya             #+#    #+#             */
/*   Updated: 2019/12/30 14:13:51 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		free_line(char **line)
{
	ft_strdel(line);
	return (0);
}

int		is_link(char *line)
{
	char**	buff;
	int		ret;

	ret = 1;
	buff = ft_strsplit(line, '-');
	if (buff == NULL || ft_chain_size(buff) != 2)
	{
		ret = 0;
		ft_chain_free(&buff);
	}
	return (ret);
}

int		is_room(char *line)
{
	char**	buff;
	int		ret;

	ret = 1;
	buff = ft_strsplit(line, ' ');
	if (buff == NULL || ft_chain_size(buff) != 3)
	{
		ret = 0;
		if (buff != NULL)
			ft_chain_free(&buff);
	}
	if (ret && (!ft_strisnum(buff[1]) || !(ft_strisnum(buff[2]))))
	{
		ret = 0;
		ft_chain_free(&buff);
	}
	return (ret);
}

int		check_line(char *line, int test_first_line)
{
	static int	start_counter = 0;
	static int	end_counter = 0;

	if (test_first_line)
	{
		if (ft_strisnum(line))
			return (1);
		return (0);
	}
	if (ft_strequ(line, START_CMD) && ++start_counter)
	{
		if (start_counter > 1)
			return (0);
	}
	if (ft_strequ(line, END_CMD) && ++end_counter)
	{
		if (end_counter > 1)
			return (0);
	}
	if (line[0] == '#')
		return (1);
	if (line[0] == 'L' || (!is_link(line) && !is_room(line)))
		return (0);
	return (1);
}

int     read_content(t_data *data)
{
	char	*line;
	int		ret;
	int		test_first_line;

	test_first_line = 1;
	data->content = NULL;
	ret = 0;
	while ((ret = get_next_line(STDOUT_FILENO, &line)) == 1)
	{
		if (ft_strlen(line) == 0 && !(ret = 0))
		{
			ft_strdel(&line);
			break ;
		}
		if (!check_line(line, test_first_line))
			return (free_line(&line));
		if (is_room(line))
			data->nr++;
		ft_chain_push(&(data->content),line);
		ft_strdel(&line);
		test_first_line = 0;
		ret = 0;
	}
	if (ret == -1)
		return (0);
	return (1);
}

int		read_all(t_data *data)
{
	if (!read_content(data))
		return (0);
	if (data->content == NULL)
		return (0);
	if ((data->na = ft_atoi(data->content[0])) <= 0)
		return (0);
	printf("ants num [%d]\n", data->na);
	return (1);
}

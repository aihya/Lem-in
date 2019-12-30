/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 11:58:57 by aihya             #+#    #+#             */
/*   Updated: 2019/12/30 19:05:39 by aihya            ###   ########.fr       */
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
	int		i;
	int		dash_counter;
	int		non_print_counter;

	i = 0;
	dash_counter = 0;
	non_print_counter = 0;
	while (line[i])
	{
		if (line[i] == '-')
			dash_counter++;
		if (!ft_isprint(line[i]))
			non_print_counter++;
		i++;
	}
	if (dash_counter != 1 && non_print_counter != 0)
		return (0);
	ret = 1;
	buff = ft_strsplit(line, '-');
	if (buff == NULL || ft_chain_size(buff) != 2)
	{
		ret = 0;
		ft_chain_free(&buff);
	}
	return (ret);
}

int		is_room(t_data* data, char *line, int inc)
{
	char**	buff;
	int		ret;

	ret = 1;
	buff = ft_strsplit(line, ' ');
	printf("line: %s\n", line);
	if (buff == NULL || ft_chain_size(buff) != 3)
	{
		printf("NULL/%zu\n", ft_chain_size(buff));
		ret = 0;
		if (buff != NULL)
			ft_chain_free(&buff);
	}
//	ft_print_chain(&buff, "\n");
	if (ret && ft_strchr(buff[0], '-'))
	{
		printf("\nDASH\n\n");
		ret = 0;
		ft_chain_free(&buff);
	}
	if (ret && (!ft_strisnum(buff[1]) || !(ft_strisnum(buff[2]))))
	{
		ret = 0;
		ft_chain_free(&buff);
	}
	data->nr = ret == 1 && inc ? data->nr + 1 : data->nr;
	return (ret);
}

int		check_line(t_data* data, char *line, int test_first_line)
{
	static int	start_counter = 0;
	static int	end_counter = 0;

//	printf("TEST_FIRST_LINE: %d\n", test_first_line);
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
	if (line[0] == 'L' || (!is_room(data, line, 1) && !is_link(line)))
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
	while ((ret = get_next_line(STDIN_FILENO, &line)) == 1)
	{
		if ((!ft_strisempty(line) || !ft_strlen(line)))
		{
			ft_strdel(&line);
			return (free_line(&line));
		}
		if (!check_line(data, line, test_first_line))
			return (free_line(&line));
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
	ft_print_chain(&(data->content), "\n");
	printf("---------------\nants num [%d]\n", data->na);
	return (1);
}

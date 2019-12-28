/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoumi <magoumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 11:58:57 by aihya             #+#    #+#             */
/*   Updated: 2019/12/28 01:04:55 by magoumi          ###   ########.fr       */
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
	int i;

	i = 0;
	while (line[i] && line[i] != '-')
		i++;
	if (i != '-')
		return (0);
	while (line[i] && line[i] != ' ')
		i++;
	if (line[i])
		return(0);
	return (1);
}

int		is_room(char *line)
{
	int i;
	int j;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	i++;
	j = 0;
	while (line[i])
	{
		if (((line[i] > '9' || line[i] < '0')) && line[i] != ' ')
			return (0);
		if (line[i] == ' ')
			j++;
		i++;
	}
	if (j > 1)
		return (0);
	return (1);
}

int		is_num(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			break ;
		if (!ft_isdigit(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int		check_line(char *line)
{
	int i;

	i = 0;
	if (line[i] == '#')
		return (1);
	if (!is_link(line) && !is_room(line) && !is_num(line))
		return (0);
	return (1);
}

int     read_content(t_data *data)
{
	char	*line;
	int		ret;

	data->content = NULL;
	ret = 0;
	while ((ret = get_next_line(STDOUT, &line)) == 1)
	{
		if (ft_strlen(line) == 0 && !(ret = 0))
		{
			ft_strdel(&line);
			break ;
		}
		if (!check_line(line))
			return (free_line(&line));
		ft_chain_push(&(data->content),line);
		ft_strdel(&line);
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
	printf("ants num [%d]\n", data->na);
	return (1);
}

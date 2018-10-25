/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 11:22:47 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/10/25 19:42:53 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

#define START 1
#define END 2

static char			add_room(t_lem_in_data *data, char **line)
{
	t_lem_in_room	room;
	t_list			*tmp;
	int				ecv;

	room.name = get_name(*line);
	room.x = get_coord(*line, 1);
	room.y = get_coord(*line, 2);
	if (!room.name || room.x < 0 || room.y < 0 || (room.neighbors = 0))
	{
		free(*line);
		return (1);
	}
	tmp = data->rooms;
	ecv = has_element(data->rooms, &room);
	if (data->rooms == NULL)
		data->rooms = ft_lstnew(&room, sizeof(room));
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		if (ecv == 0)
			tmp->next = ft_lstnew(&room, sizeof(room));
	}
	free(*line);
	return (ecv == 2 ? 1 : 0);
}

static int			velosiped(t_lem_in_data *data, char **line)
{
	int				ret;

	free(*line);
	while ((ret = get_next_line(0, line)) > 0)
	{
		data->full_input = ft_strjoin_nl_with_free_dst(data->full_input, *line);
		if (ft_strequ(*line, "##start") || ft_strequ(*line, "##end"))
		{
			free(*line);
			return (-1);
		}
		if (line[0][0] != '#')
			return (1);
		free(*line);
	}
	return (-1);
}

static char			handle_start_end(t_lem_in_data *data, char **line,
									char variant)
{
	int				gnl_ret;

	gnl_ret = velosiped(data, line);
	if (gnl_ret <= 0)
	{
		if (gnl_ret == 0)
			free(*line);
		return (1);
	}
	if ((variant == START && data->start_name) ||
		(variant == END && data->end_name))
		return (1);
	if (!is_valid_room(*line))
	{
		free(*line);
		return (1);
	}
	if (variant == START)
		data->start_name = get_name(*line);
	else if (variant == END)
		data->end_name = get_name(*line);
	return (0);
}

static char			parse_rooms(t_lem_in_data *data)
{
	char			*line;
	int				gnl_ret;

	while ((gnl_ret = get_next_line(0, &line) > 0) && is_valid_room(line))
	{
		data->full_input = ft_strjoin_nl_with_free_dst(data->full_input, line);
		if (ft_strequ("##start", line))
		{
			if (handle_start_end(data, &line, START))
				return (1);
		}
		if (ft_strequ("##end", line))
		{
			if (handle_start_end(data, &line, END))
				return (1);
		}
		if (line[0] != '#')
			add_room(data, &line);
	}
	if (gnl_ret == -1)
		return (1);
	if (is_valid_link(line))
		return (parse_neighbors(data, line));
	free(line);
	return (1);
}

char				parse(t_lem_in_data *dst)
{
	char			*line;

	get_next_line(0, &line);
	dst->full_input = ft_strjoin(line, "\n");
	dst->ants = ft_atoi(line);
	free(line);
	if (dst->ants <= 0)
		return (1);
	if (parse_rooms(dst))
		return (1);
	if (!dst->end_name || !dst->start_name || !dst->rooms)
		return (1);
	return (0);
}

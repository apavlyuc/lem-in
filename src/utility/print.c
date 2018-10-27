/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 16:56:12 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/10/27 19:18:40 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

static void			print_links(t_lem_in_room *room)
{
	t_list			*neighbors;

	neighbors = room->neighbors;
	while (neighbors)
	{
		ft_printf("%s-%s\n", room->name, (char *)neighbors->content);
		neighbors = neighbors->next;
	}
}

static void			print_rooms(t_list *list)
{
	t_lem_in_room	*room;

	while (list)
	{
		room = (t_lem_in_room *)list->content;
		list = list->next;
		ft_printf("%s %d %d\n", room->name, room->x, room->y);
		print_links(room);
	}
}

void				print_all(t_lem_in_data *data)
{
	ft_printf("\t\tDATA FROM PARSE\n");
	ft_printf("%d\n", data->ants);
	ft_printf("start: %s\n", data->start_name);
	ft_printf("end: %s\n", data->end_name);
	print_rooms(data->rooms);
	ft_printf("\t\tEND DATA\n");
	ft_printf("%s", data->full_input);
}

void				print_answer(t_list *path)
{
	while (path)
	{
		ft_printf("%s->", (char *)path->content);
		path = path->next;
	}
}

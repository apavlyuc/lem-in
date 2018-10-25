/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 19:46:47 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/10/25 19:47:08 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

char				has_element(t_list *list, t_lem_in_room *room)
{
	t_lem_in_room	*tmp;

	while (list && room)
	{
		tmp = (t_lem_in_room *)list->content;
		if (ft_strequ(tmp->name, room->name) && tmp->x == room->x
			&& tmp->y == room->y)
			return (1);
		if (ft_strequ(tmp->name, room->name))
			return (2);
		list = list->next;
	}
	return (0);
}

t_list				*find_element(t_list *list, char *name)
{
	while (list)
	{
		if (ft_strequ(((t_lem_in_room *)list->content)->name, name))
			return (list);
		list = list->next;
	}
	return (NULL);
}

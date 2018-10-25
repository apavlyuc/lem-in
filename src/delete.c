/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 16:56:30 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/10/25 18:09:20 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem-in.h>
static void			delete_neighbors(t_list *list)
{
	t_list			*tmp;

	if (!list)
		return ;
	tmp = list->next;
	while (tmp)
	{
		free(list->content);
		free(list);
		list = tmp;
		tmp = tmp->next;
	}
	free(list->content);
	free(list);
}

static void			delete_rooms(t_lem_in_data *data)
{
	t_list			*tmp;
	void			*p;

	if (!data || !data->rooms)
		return ;
	tmp = data->rooms->next;
	while (tmp)
	{
		free(((t_lem_in_room *)data->rooms->content)->name);
		p = ((t_lem_in_room *)data->rooms->content)->neighbors;
		delete_neighbors(p);
		free(data->rooms->content);
		free(data->rooms);
		data->rooms = tmp;
		tmp = tmp->next;
	}
	free(((t_lem_in_room *)data->rooms->content)->name);
	p = ((t_lem_in_room *)data->rooms->content)->neighbors;
	delete_neighbors(p);
	free(data->rooms->content);
	free(data->rooms);
}

void				delete_all(t_lem_in_data *data)
{
	ft_strdel(&data->start_name);
	ft_strdel(&data->end_name);
	ft_strdel(&data->full_input);
	delete_rooms(data);
}

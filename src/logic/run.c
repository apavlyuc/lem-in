/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 19:54:33 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/10/27 19:23:38 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
/*
static void			del(void *content, size_t size)
{
	free(content);
	(void)size;
}
*/
//										all data			answer		current room
static int			recursive_search(t_lem_in_data *all, t_list **path, t_list *cur)
{
	t_list			*path1;
	t_list			*path2;
	t_list			*names;

	path1 = NULL;
	path2 = NULL;
	names = ((t_lem_in_room *)cur->content)->neighbors;
	while (names)
	{
		names = names->next;
	}
	(void)all;
	(void)path;
	return (0);
}

void				run(t_lem_in_data *data)
{
	t_list			*path;
	t_list			*names;
	t_lem_in_room	*cur;

	cur = (t_lem_in_room *)(find_element(data->rooms, data->start_name)->content);
	names = cur->neighbors;
	path = ft_lstnew(ft_strdup(cur->name), ft_strlen(cur->name));
	recursive_search(data, &path, find_element(data->rooms, data->start_name));
	print_answer(path);
}

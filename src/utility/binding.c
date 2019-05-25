/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:43:14 by apavlyuc          #+#    #+#             */
/*   Updated: 2019/05/25 15:49:00 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/inc/libft.h"
#include "../../inc/lemin.h"

t_binding		*find_binding(t_list *links, char const *node)
{
	t_binding	*ret;

	ret = 0;
	while (links)
	{
		ret = (t_binding *)links->content;
		if (ft_strequ(ret->node, node))
			break ;
		links = links->next;
		ret = 0;
	}
	return (ret);
}

t_binding		*create_binding(char const *node, char const *neighbour)
{
	t_binding	*ret;

	ret = (t_binding *)ft_memalloc(sizeof(t_binding));
	ret->node = ft_strdup(node);
	ret->neighbours = ft_lstnew(neighbour, ft_strlen(neighbour) + 1);
	return (ret);
}

void			add_neighbour(t_binding *binding, char const *name)
{
	t_list		*new_neighbour;

	if (!binding || !(binding->neighbours))
		return ;
	new_neighbour = ft_lstnew(name, ft_strlen(name) + 1);
	ft_lstadd_before(&binding->neighbours, new_neighbour);
}

void			add_binding(t_list **links, t_binding *binding)
{
	t_list		*new_item;

	new_item = ft_lstnew(0, 0);
	new_item->content = binding;
	new_item->content_size = sizeof(*binding);
	if (!*links)
		*links = new_item;
	else
		ft_lstadd_before(links, new_item);
}

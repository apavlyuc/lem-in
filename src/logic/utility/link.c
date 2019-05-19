#include "../../../inc/lemin.h"
#include "../../../libft/inc/libft.h"

t_ull			get_list_size(t_list *lst)
{
	t_ull		ret;

	ret = 0;
	while (lst)
	{
		lst = lst->next;
		++ret;
	}
	return (ret);
}

t_link			*create_link(char *name, int id)
{
	t_link		*ret;

	ret = (t_link *)ft_memalloc(sizeof(t_link));
	ret->name = name;
	ret->id = id;
	ret->next = 0;
	return (ret);
}

t_link			*get_link_at(t_node *node, int index)
{
	int			i;
	t_link		*ret;

	i = 0;
	ret = node->link;
	while (i < index && ret)
	{
		ret = ret->next;
		++i;
	}
	return (index == i ? ret : 0);
}

void			append_to_link(t_link *link, t_link *new)
{
	while (link->next)
	{
		link = link->next;
	}
	link->next = new;
}